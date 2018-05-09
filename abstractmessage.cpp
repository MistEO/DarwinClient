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
    QString data_string;
    if (_header_map.value("Content-Type") == "text") {
        data_string = _data;
    }
    else if (_data.isEmpty()) {
        ;
    }
    else {
        data_string = QString("QByteArray data, size:"+QString::number(_data.size()));
    }
    return first_line()
            + header()
            + "\r\n"
            + data_string;
}
