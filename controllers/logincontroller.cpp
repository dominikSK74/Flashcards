#include "logincontroller.h"

LoginController::LoginController(AuthService* authService, AndroidAuthService* andoridAuthService, QObject *parent)
    : QObject{parent}, m_authService(authService), m_androidAuthService(andoridAuthService)
{

    connect(authService, &AuthService::authFailed,
        this, [this](const QString& message) {
            m_error = message;
            emit errorChanged(message);
    });

    connect(authService, &AuthService::authSuccess,
        this, [this]() {
            emit authorizationSuccess();
    });

    connect(m_androidAuthService, &AndroidAuthService::authSuccess,
            this, [this]() {
                emit authorizationSuccess();
            });

    connect(m_androidAuthService, &AndroidAuthService::authFailed,
            this, [this](const QString& message){
                m_error = message;
                emit errorChanged(message);
            });
}

void LoginController::signInWithGoogle(){
#if defined(Q_OS_ANDROID)
    m_androidAuthService->startLoginProcedure();
#else
    m_authService->startLoginProcedure();
#endif
}

void LoginController::logout(){
    m_authService->logoutProcedure();
    emit backToSignIn();
}
