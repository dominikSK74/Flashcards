#include "firebaseservice.h"
#include <QNetworkRequest>
#include <QNetworkReply>

FirebaseService::FirebaseService(Session* session, QObject *parent)
    : QObject{parent}, m_session(session)
{}
void FirebaseService::sendGetRequest(QString url) {
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString idToken = m_session->token();
    request.setRawHeader(
        "Authorization",
        QString("Bearer %1").arg(idToken).toUtf8()
    );


    QNetworkReply* reply = m_networkAccessManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this]{
        if (reply->error() != QNetworkReply::NoError) {
            emit error(reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray response = reply->readAll();

        reply->deleteLater();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            emit error(parseError.errorString());
            return;
        }
        emit finished(doc);
    });


}
