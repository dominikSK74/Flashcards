#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlContext>
#include <controllers/session.h>
#include <services/authservice.h>
#include <controllers/logincontroller.h>
#include <services/firebaseservice.h>
#include <controllers/firebasecontroller.h>
#include <services/androidauthservice.h>
#include <QSslSocket>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/temporary-logo.png"));

    QQmlApplicationEngine engine;
    Session* session = new Session();
    AuthService* authservice = new AuthService(session);
    #if defined(Q_OS_ANDROID)
    AndroidAuthService* andoridAuthService = new AndroidAuthService(session);
    LoginController* loginController = new LoginController(authservice, andoridAuthService);
    #else
    LoginController* loginController = new LoginController(authservice, nullptr);
    #endif


    qDebug() << "SSL supported:" << QSslSocket::supportsSsl()
             << "backend:" << QSslSocket::activeBackend()
             << "available:" << QSslSocket::availableBackends();


    FirebaseService* firebaseService = new FirebaseService(session);
    FirebaseController* firebaseController = new FirebaseController(firebaseService);

    engine.rootContext()->setContextProperty("loginController", loginController);
    engine.rootContext()->setContextProperty("firebaseController", firebaseController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Flashcards", "Main");

    return app.exec();
}
