#include "abstractmessage.h"

QDebug operator <<(QDebug out, const AbstractMessage & amsg)
{
    out << amsg.toString();
    return out;
}

QString AbstractMessage::toString(bool with_rap) const
{
    return first_line()
            + header()
            + "\n"
            + (_data.isEmpty() ? QString() : QString("QByteArray data, size:"+QString::number(_data.size())))
            + (with_rap?"\r\n":"");
}
