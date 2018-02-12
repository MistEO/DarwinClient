#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "clientsocket.h"
#include "requestmessage.h"
#include "responsemessage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("MrEO");
    QCoreApplication::setApplicationName("DarwinClient");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<RequestMessage>("EO.Message", 1, 0, "RequestMessage");
    qmlRegisterType<ResponseMessage>("EO.Message", 1, 0, "ResponseMessage");
    //添加上下文属性
    ClientSocket * client = new ClientSocket(&engine);
    engine.rootContext()->setContextProperty("client", client);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
