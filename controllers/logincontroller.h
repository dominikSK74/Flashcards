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

signals:
    void errorChanged(const QString &message);
    void authorizationSuccess();

private:
    AuthService* m_authService;
    QString m_error;
};

#endif // LOGINCONTROLLER_H
