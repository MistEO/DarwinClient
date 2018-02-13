#include "clientsocket.h"

#include <thread>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QTextStream>
#include <QHostAddress>
#include <QImage>

#include <QDebug>

#include "messageresource.h"

ClientSocket::ClientSocket(QObject *parent) : QObject(parent)
{
}

void ClientSocket::set_resource_class(MessageResource *res)
{
    _resource = res;
    connect(_resource, &MessageResource::appendedImage,
            this, &ClientSocket::receivedImage);
}

void ClientSocket::connectToServer(const QString & address, const int port)
{
    closeConnection();
    _client = new QTcpSocket(this);
    connect(_client, &QTcpSocket::readyRead,
            this, &ClientSocket::readMessage);
    connect(_client, &QTcpSocket::connected,
            this, &ClientSocket::connected);
    connect(_client, static_cast<void(QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
            this, &ClientSocket::_error_handler);

    _client->connectToHost(QHostAddress(address), port);
}

void ClientSocket::closeConnection()
{
    if (_client) {
        _client->abort();
        delete _client;
        _client = nullptr;
        emit closedConnection();
    }
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
    _client->write(message.toByteArray());
    qDebug() << "send message:" << message;
}

void ClientSocket::readMessage()
{
    const int bufSize = 4096;

    static QByteArray buff;
    while (!_client->atEnd()) {
        buff += _client->read(bufSize);
    }

    if (buff.endsWith("\r")) {
        //        qDebug() << buff;
        ResponseMessage message;
        message.set_source(buff);
        emit received(message.toString(false));
        qDebug() << message;
        if (_resource) {
            _resource->append_resource(message.get_header_map(), message.get_data());
        }

        buff.clear();
    }
}

void ClientSocket::_error_handler(QTcpSocket::SocketError error)
{
    Q_UNUSED(error);
    qDebug() << _client->errorString();
    emit socketError(_client->errorString());
}
