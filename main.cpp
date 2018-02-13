#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "clientsocket.h"
#include "messageresource.h"
//#include "requestmessage.h"
//#include "responsemessage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("MrEO");
    QCoreApplication::setApplicationName("DarwinClient");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MessageResource * resource = new MessageResource();
    engine.addImageProvider(QLatin1String("resource"), resource);
    ClientSocket * client = new ClientSocket(&engine);
    client->set_resource_class(resource);
    engine.rootContext()->setContextProperty("client", client);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
