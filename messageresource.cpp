#include "messageresource.h"

#include <QDebug>
#include <QCoreApplication>

MessageResource::MessageResource(bool keep_resource)
    : QQuickImageProvider(QQuickImageProvider::Image),
      _keep_resource(keep_resource)
{

}

MessageResource::~MessageResource()
{
    if (_keep_resource) {
        for (auto fileinfo : _image_fileinfos) {
            QFile(fileinfo.fileName()).remove();
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
            QFileInfo fileinfo = QString::number(_image_fileinfos.size()) + ".jpg";
            dst.save(fileinfo.fileName());
            _image_fileinfos.append(fileinfo);
            emit appendedImage(_image_fileinfos.size() - 1);
        }
        else {
            _unkeep_image = dst;
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
        image.load(_image_fileinfos[index].fileName());
        return image;
    }
    else {
        Q_UNUSED(id);
        return _unkeep_image;
    }
}
