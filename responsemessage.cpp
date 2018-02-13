#include "responsemessage.h"

#include <QString>
#include <QStringList>
#include <QDebug>

ResponseMessage::ResponseMessage(QObject *parent)
    : AbstractMessage(parent)
{
}

void ResponseMessage::set_source(const QByteArray &source)
{
    _source = source;
    _unpack(source);
}

void ResponseMessage::_unpack(const QByteArray &source)
{
    QStringList lines = QString(source).split("\n");
    if (lines.size() < 2) {
        qCritical() << "Response message segmentation error:" << QString(source);
        return;
    }
    auto iter = lines.begin();
    _status_line = *iter;
    _unpack_status_line(*iter);

    _header.clear();
    _header_map.clear();
    for (++iter; iter != lines.end() && !iter->isEmpty(); ++iter) {
        _header += *iter + "\n";
        _unpack_header_line(*iter);
    }

    int data_pos = (first_line() + header() + "\n").length();
    _data = source.mid(data_pos, source.size()-2);

    if (_header_map["Content-Type"] == "Image") {
        QImage img = data_object<QImage>();
    }
}

void ResponseMessage::_unpack_status_line(const QString &status_line)
{
    QStringList words = status_line.split(" ");
    if (words.size() < 3) {
        qCritical() << "Response status segmentation error:" << status_line;
        return;
    }
    _version = words[0];
    _status = words[1].toInt();
    _status_name.clear();
    for (auto i = words.begin() + 2; i != words.end(); ++i) {
        if (!_status_name.isEmpty()) {
            _status_name += " ";
        }
        _status_name += *i;
    }
}

void ResponseMessage::_unpack_header_line(const QString &header_line)
{
    QStringList pair = header_line.split(":");
    if (pair.size() != 2) {
        qCritical() << "Response header segmentation error:" << header_line;
        return;
    }
    _header_map[pair[0]] = pair[1];
}

QString ResponseMessage::first_line() const
{
    return _status_line + "\n";
}

QString ResponseMessage::header() const
{
    return _header;
}

const QMap<QString, QString> & ResponseMessage::get_header_map() const
{
    return _header_map;
}

const QString & ResponseMessage::get_version() const
{
    return _version;
}

const QByteArray & ResponseMessage::get_data() const
{
    return _data;
}

QByteArray ResponseMessage::toByteArray() const
{
    return _source;
}
