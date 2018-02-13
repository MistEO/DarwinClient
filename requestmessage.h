#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

#include "abstractmessage.h"

class RequestMessage : public AbstractMessage
{
    Q_OBJECT
public:
    explicit RequestMessage(QObject * parent = nullptr);

    QMap<QString, QString> & header_map();
    QString & version();
    QByteArray & data();
    QByteArray toByteArray() const;

    QString request_type;
    QString resource_type;
signals:

public slots:
    QString first_line() const;
    QString header() const;
};

#endif // REQUESTMESSAGE_H
