#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>
#include <QTextCodec>

#include "clientsocket.h"
#include "messageresource.h"
//#include "requestmessage.h"
//#include "responsemessage.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("MrEO");
    QCoreApplication::setApplicationName("DarwinClient");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MessageResource * resource = new MessageResource();
    engine.addImageProvider(QLatin1String("resource"), resource);
    engine.rootContext()->setContextProperty("resource", resource);
    ClientSocket * client = new ClientSocket(&engine);
    client->set_resource_object(resource);
    engine.rootContext()->setContextProperty("client", client);

    MessageResource * cameraResource = new MessageResource(false);
    engine.addImageProvider(QLatin1String("cameraResource"), cameraResource);
    engine.rootContext()->setContextProperty("cameraResource", cameraResource);
    ClientSocket * cameraClient = new ClientSocket(&engine);
    cameraClient->set_resource_object(cameraResource);
    engine.rootContext()->setContextProperty("cameraClient", cameraClient);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
