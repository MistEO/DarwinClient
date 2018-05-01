#ifndef MESSAGERESOURCE_H
#define MESSAGERESOURCE_H

#include <QObject>
#include <QQuickImageProvider>
#include <QVector>
#include <QImage>
#include <QFileInfo>

class MessageResource :public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit MessageResource(bool keep_resource = true);
    ~MessageResource();

    void append_resource(const QMap<QString, QString> & header_map, const QByteArray & data);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

signals:
    void appendedImage(int index);
    void appendedAudio(int index);
public slots:
private:
    QVector<QFileInfo> _image_fileinfos;
    QImage _unkeep_image;
    bool _keep_resource;
};
#endif // MESSAGERESOURCE_H
