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
    Q_INVOKABLE void sendRawText(const QString & text);
    Q_INVOKABLE void sendGetImage();

    Q_INVOKABLE QString getAddress() const;
    Q_INVOKABLE quint16 getPort() const;
    Q_INVOKABLE QString getName() const;
signals:
    void connected();
    void socketError(const QString & error_string);
    void receivedStatus(const QString & text);
    void receivedImage(const QImage & image);
public slots:
    void readMessage();
private:
    void _error_handler(QTcpSocket::SocketError error);
    
    QString _pack_request_line(const QString & request, const QString & source, const QString & version = QString("HTTP/1.1")) const;
    
    QTcpSocket * _client = nullptr;
};

#endif // SOCKETPARSER_H
