#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

#include "requestmessage.h"
#include "responsemessage.h"

class MessageResource;

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);
    void set_resource_object(MessageResource * res);
    Q_INVOKABLE void connectToServer(
            const QString & address = QString("127.0.0.1"),
            const int port = 1240);
    Q_INVOKABLE void closeConnection();
    Q_INVOKABLE void sendMessage(const RequestMessage & message);
    Q_INVOKABLE void sendInputText(const QString & text);

    Q_INVOKABLE QString getAddress() const;
    Q_INVOKABLE quint16 getPort() const;
    Q_INVOKABLE QString getName() const;
signals:
    void connected();
    void closedConnection();
    void received(const QString & message_string);
    void receivedImage(int id);
    void socketError(const QString & error_string);
public slots:
    void readMessage();
private:
    void _error_handler(QTcpSocket::SocketError error);
    
    QTcpSocket * _client = nullptr;
    MessageResource * _resource = nullptr;
};

#endif // ClientSocket_H
