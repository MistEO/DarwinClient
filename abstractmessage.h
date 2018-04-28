#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QString>
#include <QMap>
#include <QByteArray>
#include <QDebug>

class AbstractMessage
{
public:
    AbstractMessage() = default;
    virtual ~AbstractMessage() = default;

    friend QDebug operator <<(QDebug out, const AbstractMessage & amsg);

    QString toString() const;
    virtual QByteArray toByteArray() const = 0;
    virtual QString first_line() const = 0;
    virtual QString header() const = 0;
protected:
    QMap<QString, QString> _header_map;
    QString _version = "HTTP/1.1";
    QByteArray _data;
};

#endif // ABSTRACTMESSAGE_H
