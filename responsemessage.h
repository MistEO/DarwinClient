#ifndef RESPONSEMESSAGE_H
#define RESPONSEMESSAGE_H

#include <QImage>

#include "abstractmessage.h"

class ResponseMessage : public AbstractMessage
{
public:
    ResponseMessage() = default;
    ResponseMessage(const QByteArray &source);
    ~ResponseMessage() = default;
    void set_source(const QByteArray & source);
    const QMap<QString, QString> & get_header_map() const;
    const QString & get_version() const;
    const QByteArray & get_data() const;
    QByteArray toByteArray() const;

    QString first_line() const;
    QString header() const;

    bool completed() const;

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

#endif // RESPONSEMESSAGE_H
