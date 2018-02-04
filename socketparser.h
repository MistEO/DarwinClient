#ifndef SOCKETPARSER_H
#define SOCKETPARSER_H

#include <QObject>
#include <QTcpSocket>

class SocketParser : public QObject
{
    Q_OBJECT
public:
    explicit SocketParser(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(
            const QString & address = QString("127.0.0.1"),
            const int port = 1240);
    Q_INVOKABLE void sendText(const QString & text);
signals:
    void connected();
    void socketError(const QString & error_string);
    void received(const QString & text);
public slots:
    void readMessage();
private:
    void error_handler(QTcpSocket::SocketError error);
    QTcpSocket * m_client = nullptr;
};

#endif // SOCKETPARSER_H
