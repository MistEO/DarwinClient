#include "socketparser.h"

#include <thread>

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QTextStream>
#include <QHostAddress>

#include <QDebug>

SocketParser::SocketParser(QObject *parent) : QObject(parent)
{

}

void SocketParser::connectToServer(const QString & address, const int port)
{
    delete m_client;
    m_client = new QTcpSocket(this);
    connect(m_client, &QTcpSocket::readyRead,
            this, &SocketParser::readMessage);
    connect(m_client, &QTcpSocket::connected,
            this, &SocketParser::connected);
    connect(m_client, static_cast<void(QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
            this, &SocketParser::error_handler);

    m_client->abort();
    m_client->connectToHost(QHostAddress(address), port);
}

void SocketParser::sendText(const QString &text)
{
    QDataStream out(m_client);
    qDebug() << "send text" << text;
    out << text;
}

void SocketParser::readMessage()
{
    QDataStream in(m_client);
    QString message;
    in >> message;
    qDebug() << "read message" << message;
    emit received(message);
}

void SocketParser::error_handler(QTcpSocket::SocketError error)
{
    Q_UNUSED(error);
    qDebug() << m_client->errorString();
    emit socketError(m_client->errorString());
}
