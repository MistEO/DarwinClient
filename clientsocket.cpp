#include "clientsocket.h"

#include <thread>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QTextStream>
#include <QHostAddress>
#include <QImage>

#include <QDebug>

ClientSocket::ClientSocket(QObject *parent) : QObject(parent)/*, QQuickImageProvider(QQuickImageProvider::Image)*/
{
}

void ClientSocket::connectToServer(const QString & address, const int port)
{
    if (_client) {
        _client->abort();
    }
    delete _client;
    _client = new QTcpSocket(this);
    connect(_client, &QTcpSocket::readyRead,
            this, &ClientSocket::readMessage);
    connect(_client, &QTcpSocket::connected,
            this, &ClientSocket::connected);
    connect(_client, static_cast<void(QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
            this, &ClientSocket::_error_handler);

    _client->connectToHost(QHostAddress(address), port);
}

QString ClientSocket::getAddress() const
{
    return _client->peerAddress().toString();
}

quint16 ClientSocket::getPort() const
{
    return _client->peerPort();
}

QString ClientSocket::getName() const
{
    return _client->peerName();
}

void ClientSocket::sendInputText(const QString &text)
{
    RequestMessage message;
    QStringList words = text.split(" ");
    if (words.size() < 2) {
        qDebug() << "Input text segmentation error:" << text;
        return;
    }
    message.request_type = words[0];
    message.resource_type = words[1];
    if (words.size() >= 3) {
        message.version() = words[2];
    }
    sendMessage(message);
}

void ClientSocket::sendMessage(const RequestMessage &message)
{
    QTextStream out(_client);
    qDebug() << "send message:" << message;
    out << message;
}

void ClientSocket::readMessage()
{
    ResponseMessage message;
    message.set_source(_client->readAll());
    emit received(message);
    qDebug() << message;
}

void ClientSocket::_error_handler(QTcpSocket::SocketError error)
{
    Q_UNUSED(error);
    qDebug() << _client->errorString();
    emit socketError(_client->errorString());
}
