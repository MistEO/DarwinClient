#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "socketparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("MrEO");
    QCoreApplication::setApplicationName("DarwinClient");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //添加上下文属性
    SocketParser * client = new SocketParser(&engine);
    engine.rootContext()->setContextProperty("client", client);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
