#ifndef RESPONSEMESSAGE_H
#define RESPONSEMESSAGE_H

#include <QImage>

#include "abstractmessage.h"

class ResponseMessage : public AbstractMessage
{
    Q_OBJECT
public:
    explicit ResponseMessage(QObject *parent = nullptr);

    void set_source(const QByteArray & source);
    const QMap<QString, QString> & get_header_map() const;
    const QString & get_version() const;
    const QByteArray & get_data() const;
    QByteArray toByteArray() const;

    template<typename Ty>
    Ty data_object() const;

public slots:
    QString first_line() const;
    QString header() const;

private:
    void _unpack(const QByteArray & source);
    void _unpack_status_line(const QString & status_line);
    void _unpack_header_line(const QString & header_line);

    QString _status_line;
    int _status;
    QString _status_name;
    QString _header;
    QByteArray _source;
};

template<typename Ty>
Ty ResponseMessage::data_object() const
{
    if (typeid(Ty) == typeid(QImage)) {
        QImage dst(static_cast<const uchar*>((void*)_data.constData()),
                   _header_map["Cols"].toInt(),
                _header_map["Rows"].toInt(),
                _header_map["Step"].toInt(),
                QImage::Format_RGB888);
        return dst;
    }
    return Ty();
}

#endif // RESPONSEMESSAGE_H
