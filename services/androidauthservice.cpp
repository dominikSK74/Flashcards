
#include "androidauthservice.h"
#include <QSettings>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QCoreApplication>
#endif

AndroidAuthService::AndroidAuthService(Session* session, QObject *parent)
    : QObject{parent}, m_session(session)
{
#if defined(Q_OS_ANDROID)
    AndroidAuthService::setInstanceForJni(this);
#endif
    QSettings settings(":config.ini", QSettings::IniFormat);
    m_googleWebClientId = settings.value("googleWebClientId").toString();
    m_firebaseApiKey = settings.value("firebaseApiKey").toString();

    qDebug() << m_googleWebClientId;

    connect(this, &AndroidAuthService::idTokenReceived,
            this, [this](const QString& jwtIdToken) {
                exchangeGoogleTokenToFirebase(jwtIdToken);
            });

    connect(this, &AndroidAuthService::signInError,
            this, [this](const QString& message){
                emit authFailed(message);
            });
}

void AndroidAuthService::signIn(const QString& webClientId, bool filterAuthorizedAccounts)
{
#if defined(Q_OS_ANDROID)

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    if (!activity.isValid()) {
        emit signInError("No Android Activity/Context available");
        return;
    }

    QJniObject jWebClientId = QJniObject::fromString(webClientId);

    QJniObject::callStaticMethod<void>(
        "pl/fc/auth/QtGoogleAuth",
        "signIn",
        "(Landroid/app/Activity;Ljava/lang/String;Z)V",
        activity.object(),
        jWebClientId.object<jstring>(),
        (jboolean)filterAuthorizedAccounts
        );
#endif
}

void AndroidAuthService::exchangeGoogleTokenToFirebase(const QString &googleIdToken)
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

void AndroidAuthService::startLoginProcedure() {
    signIn(m_googleWebClientId, false);
}
