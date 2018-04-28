#include "abstractmessage.h"

//const char* HttpException::what() const noexcept
//{
//    return _message.c_str();
//}

QDebug operator <<(QDebug out, const AbstractMessage & amsg)
{
    out << amsg.toString();
    return out;
}

QString AbstractMessage::toString() const
{
    return first_line()
            + header()
            + "\r\n"
            + (_data.isEmpty() ? QString() : QString("QByteArray data, size:"+QString::number(_data.size())));
}
