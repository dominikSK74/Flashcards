#ifndef FIREBASECONTROLLER_H
#define FIREBASECONTROLLER_H

#include <QObject>
#include <services/firebaseservice.h>
#include <models/objects/cardobject.h>

class FirebaseController : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseController(FirebaseService* firebaseService, QObject *parent = nullptr);
    Q_INVOKABLE void testConnection();

    Q_INVOKABLE void loadSets();
    Q_INVOKABLE void saveSet(QString setId, QString setName, QList<CardObject> list, QJsonDocument doc);
    QJsonObject prepareCardsJsonBody(QString uuid, QString setId, QList<CardObject> list);
    QJsonObject prepareDeleteCardsJsonBody(QJsonDocument doc);
    Q_INVOKABLE void loadCards(QString setId);

signals:
    void logout();
    void setsLoaded(const QJsonDocument &data);
    void addingSetCompleted();
    void cardsLoaded(const QJsonDocument &data);

private:
    FirebaseService* m_firebaseService;
};

#endif // FIREBASECONTROLLER_H
