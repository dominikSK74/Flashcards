#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>
#include <controllers/session.h>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QNetworkAccessManager>

class AuthService : public QObject
{
    Q_OBJECT
public:
    AuthService(Session* session, QObject* parent = nullptr);
    void exchangeGoogleTokenToFirebase(const QString &googleIdToken);
    void startLoginProcedure();

private:
    QString m_googleClientId;
    QString m_firebaseApiKey;
    QString m_googleIdToken;
    QNetworkAccessManager m_network_access_manager;
    QOAuth2AuthorizationCodeFlow* m_oauth = nullptr;
    QOAuthHttpServerReplyHandler* m_replyHandler = nullptr;
    Session *m_session = nullptr;

signals:
    void authFailed(const QString &message);
    void authSuccess();
};

#endif // AUTHSERVICE_H
