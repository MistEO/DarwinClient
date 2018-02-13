#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

#include "abstractmessage.h"

class RequestMessage : public AbstractMessage
{
public:
    RequestMessage() = default;
    ~RequestMessage() = default;
    QMap<QString, QString> & header_map();
    QString & version();
    QByteArray & data();
    QString first_line() const;
    QString header() const;
    QByteArray toByteArray() const;

    QString request_type;
    QString resource_type;
};

#endif // REQUESTMESSAGE_H
