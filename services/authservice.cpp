#include "authservice.h"
#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QSet>
#include <QNetworkReply>
#include <QSettings>
#include <QDir>

AuthService::AuthService(Session* session, QObject* parent) : QObject(parent), m_session(session) {
    QSettings settings(":config.ini", QSettings::IniFormat);

    m_googleClientId = settings.value("googleClientId").toString();
    m_firebaseApiKey = settings.value("firebaseApiKey").toString();

    qDebug() << m_googleClientId;

    m_oauth = new QOAuth2AuthorizationCodeFlow(&m_network_access_manager, this);
    m_oauth->setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/v2/auth"));
    m_oauth->setTokenUrl(QUrl("https://oauth2.googleapis.com/token"));
    m_oauth->setClientIdentifier(m_googleClientId);
    m_oauth->setRequestedScopeTokens(QSet<QByteArray>{
        "openid", "email", "profile"
    });

    m_oauth->setPkceMethod(QOAuth2AuthorizationCodeFlow::PkceMethod::S256);


    const int port = 5000;
    m_replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    m_oauth->setReplyHandler(m_replyHandler);

    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
        this, [](const QUrl &url) {
        QDesktopServices::openUrl(url);
    });

    m_oauth->setModifyParametersFunction([](QAbstractOAuth::Stage stage,
        QMultiMap<QString, QVariant> *params) {

        if (stage == QAbstractOAuth::Stage::RequestingAuthorization) {
            params->insert("access_type", "offline");
            params->insert("prompt", "consent");
            params->insert("include_granted_scopes", "true");
        }
    });


    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::granted, this, [this] {
        const QString googleIdToken = m_oauth->idToken();
        if (googleIdToken.isEmpty()) {
            emit authFailed("No idToken from Google (idToken() is empty).");
            return;
        }

        m_googleIdToken = googleIdToken;
        exchangeGoogleTokenToFirebase(m_googleIdToken);
    });


    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::requestFailed, this,
        [this](const QAbstractOAuth::Error err) {
        Q_UNUSED(err);
        emit authFailed("OAuth request failed (Google)");
    });
}


void AuthService::exchangeGoogleTokenToFirebase(const QString &googleIdToken)
{
    QUrl url(QString("https://identitytoolkit.googleapis.com/v1/accounts:signInWithIdp?key=%1")
                 .arg(m_firebaseApiKey));

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QUrlQuery postBody;
    postBody.addQueryItem("id_token", googleIdToken);
    postBody.addQueryItem("providerId", "google.com");

    QJsonObject payload;
    payload["requestUri"] = "http://localhost";
    payload["postBody"] = postBody.toString(QUrl::FullyEncoded);
    payload["returnSecureToken"] = true;

    auto reply = m_network_access_manager.post(req, QJsonDocument(payload).toJson());


    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        const auto data = reply->readAll();
        reply->deleteLater();

        const auto doc = QJsonDocument::fromJson(data);
        if (!doc.isObject()) {
            emit authFailed("Incorrect response from Firebase.");
            return;
        }

        const auto obj = doc.object();
        if (obj.contains("error")) {
            emit authFailed(QString("Firebase error: %1").arg(QString::fromUtf8(data)));
            return;
        }

        QString firebaseIdToken = obj.value("idToken").toString();
        if (firebaseIdToken.isEmpty()) {
            emit authFailed("Error id");
            return;
        }

        m_session->setToken(firebaseIdToken);
        emit authSuccess();
    });

}

void AuthService::startLoginProcedure() {
    m_oauth->grant();
}
