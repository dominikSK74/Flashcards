#include "firebaseservice.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>

FirebaseService::FirebaseService(Session* session, QObject *parent)
    : QObject{parent}, m_session(session)
{}
void FirebaseService::sendGetRequest(QString url, QString operationName) {
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString idToken = m_session->token();
    request.setRawHeader(
        "Authorization",
        QString("Bearer %1").arg(idToken).toUtf8()
    );


    QNetworkReply* reply = m_networkAccessManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this, operationName]{
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
        emit finished(doc, operationName);
    });


}

void FirebaseService::sendPostRequest(QString url, QJsonObject body, QString operationName){

    QNetworkRequest request{ QUrl(url) };
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization",
                         ("Bearer " + m_session->token()).toUtf8());

    QNetworkReply* reply = m_networkAccessManager.post(request, QJsonDocument(body).toJson());

    connect(reply, &QNetworkReply::finished, this, [reply, this, operationName]{
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
        emit finished(doc, operationName);
    });
}

void FirebaseService::sendPatchRequest(QString url, QJsonObject body, QString operationName){

    QNetworkRequest request{ QUrl(url) };
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization",
                         ("Bearer " + m_session->token()).toUtf8());

    QByteArray payload = QJsonDocument(body).toJson();
    QNetworkReply *reply =
        m_networkAccessManager.sendCustomRequest(request, "PATCH", payload);


    connect(reply, &QNetworkReply::finished, this, [reply, this, operationName]{
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
        emit finished(doc, operationName);
    });
}

QString FirebaseService::getUUID() {
    return m_session->uuid();
}

void FirebaseService::sendDeleteRequest(QString url, QString operationName){

    QNetworkRequest request{ QUrl(url) };
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization",
                         ("Bearer " + m_session->token()).toUtf8());

    QNetworkReply* reply = m_networkAccessManager.deleteResource(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this, operationName]{
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
        emit finished(doc, operationName);
    });
}
