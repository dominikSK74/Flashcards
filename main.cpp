#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlContext>
#include <controllers/session.h>
#include <services/authservice.h>
#include <controllers/logincontroller.h>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/temporary-logo.png"));

    QQmlApplicationEngine engine;
    Session* session = new Session();
    AuthService* authservice = new AuthService(session);
    LoginController* loginController = new LoginController(authservice);

    engine.rootContext()->setContextProperty("loginController", loginController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Flashcards", "Main");

    return app.exec();
}
