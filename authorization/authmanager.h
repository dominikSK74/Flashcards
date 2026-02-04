#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QNetworkAccessManager>

class AuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firebaseIdToken READ firebaseIdToken NOTIFY firebaseIdTokenChanged)
public:
    explicit AuthManager(QObject *parent = nullptr);

    Q_INVOKABLE void signInWithGoogle();
    Q_INVOKABLE void signOut();
    QString firebaseIdToken() const { return m_firebaseIdToken; }

signals:
    void firebaseIdTokenChanged();
    void errorOccurred(const QString &message);

private:
    void exchangeGoogleTokenToFirebase(const QString &googleIdToken);

    QNetworkAccessManager m_network_access_manager;
    QOAuth2AuthorizationCodeFlow* m_oauth = nullptr;
    QOAuthHttpServerReplyHandler* m_replyHandler = nullptr;

    QString m_googleIdToken;
    QString m_firebaseIdToken;

    QString m_googleClientId;
    QString m_googleClientSecret;
    QString m_firebaseApiKey;
};

#endif // AUTHMANAGER_H
