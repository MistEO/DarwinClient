#include "abstractmessage.h"

AbstractMessage::AbstractMessage(QObject *parent) : QObject(parent)
{

}

QDebug operator <<(QDebug out, const AbstractMessage & amsg)
{
    out << amsg.toString();
    return out;
}

QString AbstractMessage::toString() const
{
    return QString("%1%2\n").arg(first_line()).arg(header())
            + (_data.isEmpty() ? QString() : QString("QByteArray data, size:"+QString::number(_data.size())))
            + "\r\n";
}
