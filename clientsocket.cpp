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

void ClientSocket::set_resource_object(MessageResource *res)
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

QString ClientSocket::sendInputText(const QString &url,
                                 const QString & method,
                                 const QString & header,
                                 const QString & data)
{
    RequestMessage message;
    message.request_type = method;
    message.resource_type = url;
    if (!header.isEmpty()) {
        QStringList header_list = header.split("\\n");
        for (auto header : header_list) {
            QStringList key_value = header.split(":");
            if (key_value.size() != 2) {
                continue;
            }
            message.header_map()[key_value[0]] = key_value[1];
        }
    }
    if (!data.isEmpty()) {
        message.data() = data.toLocal8Bit();
    }
    sendMessage(message);
    return message.toString();
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

    if (buff.endsWith("\r\n")) {
        //        qDebug() << buff;
        ResponseMessage message;
        message.set_source(buff);
        emit received(message.toString());
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
