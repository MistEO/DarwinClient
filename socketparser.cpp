#include "socketparser.h"

#include <thread>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QTextStream>
#include <QHostAddress>
#include <QImage>

#include <QDebug>

SocketParser::SocketParser(QObject *parent) : QObject(parent)
{

}

void SocketParser::connectToServer(const QString & address, const int port)
{
    if (_client) {
        _client->abort();
    }
    delete _client;
    _client = new QTcpSocket(this);
    connect(_client, &QTcpSocket::readyRead,
            this, &SocketParser::readMessage);
    connect(_client, &QTcpSocket::connected,
            this, &SocketParser::connected);
    connect(_client, static_cast<void(QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
            this, &SocketParser::_error_handler);

    _client->connectToHost(QHostAddress(address), port);
}

QString SocketParser::getAddress() const
{
    return _client->peerAddress().toString();
}

quint16 SocketParser::getPort() const
{
    return _client->peerPort();
}

QString SocketParser::getName() const
{
    return _client->peerName();
}

void SocketParser::sendRawText(const QString &text)
{
    QTextStream out(_client);
    qDebug() << "send text:" << text;
    out << text;
}

void SocketParser::readMessage()
{
    //    QDataStream in(_client);
    QByteArray message(_client->readAll());
    QString text = message.left(message.indexOf("\n\n"));
    qDebug() << text;
    receivedStatus(text);
    QImage image = QImage::fromData(message.right(message.indexOf("\n\n")+QString("\n\n").size()));
    receivedImage(image);
}

void SocketParser::_error_handler(QTcpSocket::SocketError error)
{
    Q_UNUSED(error);
    qDebug() << _client->errorString();
    emit socketError(_client->errorString());
}

void SocketParser::sendGetImage()
{
    sendRawText(_pack_request_line("GET", "IMAGE"));
}

QString SocketParser::_pack_request_line(const QString &request, const QString &source, const QString &version) const
{
    return QString("%1 %2 %3\n").arg(request).arg(source).arg(version);
}
