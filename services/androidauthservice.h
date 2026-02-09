#ifndef ANDROIDAUTHSERVICE_H
#define ANDROIDAUTHSERVICE_H

#include <QObject>
#include <controllers/session.h>
#include <QNetworkAccessManager>

class AndroidAuthService : public QObject
{
    Q_OBJECT
public:
    explicit AndroidAuthService(Session* session, QObject *parent = nullptr);

    void signIn(const QString& webClientId, bool filterAuthorizedAccounts = false);
    static void setInstanceForJni(AndroidAuthService* inst);
    void startLoginProcedure();
    void exchangeGoogleTokenToFirebase(const QString &googleIdToken);


signals:    
    void idTokenReceived(const QString& jwtIdToken);
    void signInError(const QString& message);
    void authFailed(const QString &message);
    void authSuccess();

private:
    QString m_googleWebClientId;
    QString m_firebaseApiKey;
    QString m_googleIdToken;
    Session *m_session = nullptr;
    QNetworkAccessManager m_network_access_manager;
};

#endif // ANDROIDAUTHSERVICE_H
