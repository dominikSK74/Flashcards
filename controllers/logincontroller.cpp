#include "logincontroller.h"

LoginController::LoginController(AuthService* authService, QObject *parent)
    : QObject{parent}, m_authService(authService)
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
}

void LoginController::signInWithGoogle(){
    m_authService->startLoginProcedure();
}
