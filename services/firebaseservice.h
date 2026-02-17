#ifndef FIREBASESERVICE_H
#define FIREBASESERVICE_H

#include <QObject>
#include <controllers/session.h>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class FirebaseService : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseService(Session* session, QObject *parent = nullptr);
    void sendGetRequest(QString url, QString operationName);
    void sendPostRequest(QString url, QJsonObject body, QString operationName);
    QString getUUID();
signals:
    void finished(QJsonDocument doc, QString operationName);
    void error(QString msg);

private:
    QNetworkAccessManager m_networkAccessManager;
    Session* m_session;
};

#endif // FIREBASESERVICE_H
