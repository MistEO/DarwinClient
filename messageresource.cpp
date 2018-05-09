#include "messageresource.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>

MessageResource::MessageResource(bool keep_resource)
    : QQuickImageProvider(QQuickImageProvider::Image),
      _keep_resource(keep_resource)
{

}

MessageResource::~MessageResource()
{
    if (_keep_resource) {
        for (auto fileinfo : _image_fileinfos) {
            QFile(fileinfo.filePath()).remove();
        }
    }
}

void MessageResource::append_resource(const QMap<QString, QString> &header_map, const QByteArray &data)
{
    if (header_map["Content-Type"] == "image") {
//        if (data.size() != header_map["Content-Length"].toInt()) {
//            qDebug() << "data size error: " << data.size();
//            return;
//        }
        QImage dst(static_cast<const uchar*>((void*)data.constData()),
                   header_map["Cols"].toInt(),
                header_map["Rows"].toInt(),
                header_map["Step"].toInt(),
                QImage::Format_RGB888);
        if (_keep_resource) {
            static const QString temp_dir = "temp/";
            QDir dir(temp_dir);
            if (!dir.exists()){
                dir.mkpath(".");
            }
            QFileInfo fileinfo = temp_dir + QString::number(_image_fileinfos.size()) + ".png";
            dst.save(fileinfo.filePath(), "png", 100);
            _image_fileinfos.append(fileinfo);
            emit appendedImage(_image_fileinfos.size() - 1);
        }
        else {
            image_locker.lock();
            _unkeep_image = dst;
            image_locker.unlock();
            emit appendedImage(0);
        }
    }
}

QImage MessageResource::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    if (_keep_resource) {
        int index = id.toInt();

        qDebug() << "request image" << index;
        if (index < 0 || index >= _image_fileinfos.size()) {
            qCritical() << "message resource request image cross:" << id;
            return QImage();
        }
        qDebug() << _image_fileinfos[index];
        QImage image;
        image.load(_image_fileinfos[index].filePath());
        return image;
    }
    else {
        Q_UNUSED(id);
        return _unkeep_image;
    }
}

bool MessageResource::saveImage(const QString& id, const QString& filename)
{

    if (_keep_resource) {
        int index = id.toInt();

        qDebug() << "save image" << index;
        if (index < 0 || index >= _image_fileinfos.size()) {
            qCritical() << "message resource request image cross:" << id;
            return false;
        }
        QString dst_filename =
                filename.isEmpty()
                ? (QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss") + ".png")
                : filename;
        QFile::copy(_image_fileinfos[index].filePath(), dst_filename);
    }
    else {
        QString dst_filename =
                filename.isEmpty()
                ? (QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss") + ".png")
                : filename;
        image_locker.lock();
        _unkeep_image.save(dst_filename, "png", 100);
        image_locker.unlock();
    }
}
