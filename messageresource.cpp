#include "messageresource.h"

#include <QDebug>

MessageResource::MessageResource(bool keep_resource)
    : QQuickImageProvider(QQuickImageProvider::Image),
      _keep_resource(keep_resource)
{

}

void MessageResource::append_resource(const QMap<QString, QString> &header_map, const QByteArray &data)
{
    if (header_map["Content-Type"] == "image") {
        QByteArray dst_data = data;
        if (dst_data.endsWith("\r\n")) {
            dst_data.remove(dst_data.length()-3, 2);
        }
        QImage dst(static_cast<const uchar*>((void*)dst_data.constData()),
                   header_map["Cols"].toInt(),
                header_map["Rows"].toInt(),
                header_map["Step"].toInt(),
                QImage::Format_RGB888);
        if (_keep_resource) {
            _image_list.append(dst);
            emit appendedImage(_image_list.size() - 1);
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
        if (index < 0 || index >= _image_list.size()) {
            qCritical() << "message resource request image cross:" << id;
            return QImage();
        }
        return _image_list[index];
    }
    else {
        Q_UNUSED(id);
        return _unkeep_image;
    }
}
