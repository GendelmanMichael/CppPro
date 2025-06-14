#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <Model.h>
#include <Controller.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TempModel* model = new TempModel(0);
    TempController* controller = new TempController(model);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("model", model);
    engine.rootContext()->setContextProperty("controller", controller);
    engine.loadFromModule("Temperatures", "Main");

    return app.exec();
}
