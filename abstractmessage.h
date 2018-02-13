#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QDebug>

class AbstractMessage : public QObject
{
    Q_OBJECT
public:
    explicit AbstractMessage(QObject *parent = nullptr);
    friend QDebug operator <<(QDebug out, const AbstractMessage & amsg);

    Q_INVOKABLE QString toString() const;
    virtual QByteArray toByteArray() const = 0;
protected:
    QMap<QString, QString> _header_map;
    QString _version = "HTTP/1.1";
    QByteArray _data;

public slots:
    virtual QString first_line() const = 0;
    virtual QString header() const = 0;
};

#endif // ABSTRACTMESSAGE_H
