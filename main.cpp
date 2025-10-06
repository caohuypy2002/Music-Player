#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "musicloader.h"
#include <QQmlContext>
#include "customimage.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<MusicLoader>("MusicLoader",1,0,"MusicLoader");
    qmlRegisterType<CustomImage>("CustomImage", 1, 0, "CustomImage");
    const QUrl url(QStringLiteral("qrc:/ASSIGMENT_MusicPlayer/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
