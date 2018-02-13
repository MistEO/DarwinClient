#include "messageresource.h"

#include <QDebug>

MessageResource::MessageResource()
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

void MessageResource::append_resource(const QMap<QString, QString> &header_map, const QByteArray &data)
{
    if (header_map["Content-Type"] == "Image") {
        QImage dst(static_cast<const uchar*>((void*)data.constData()),
                   header_map["Cols"].toInt(),
                header_map["Rows"].toInt(),
                header_map["Step"].toInt(),
                QImage::Format_RGB888);
        _image_list.append(dst);
        emit appendedImage(_image_list.size() - 1);
    }
}

QImage MessageResource::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    int index = id.toInt();

    qDebug() << "request image" << index;
    if (index < 0 || index >= _image_list.size()) {
        qCritical() << "message resource request image cross:" << id;
        return QImage();
    }
    return _image_list[index];
}
