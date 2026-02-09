#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <services/authservice.h>

class LoginController : public QObject
{
    Q_OBJECT
public:
    explicit LoginController(AuthService* authService, QObject *parent = nullptr);
    Q_INVOKABLE void signInWithGoogle();
    Q_INVOKABLE void logout();

signals:
    void errorChanged(const QString &message);
    void authorizationSuccess();
    void backToSignIn();

private:
    AuthService* m_authService;
    QString m_error;
};

#endif // LOGINCONTROLLER_H
