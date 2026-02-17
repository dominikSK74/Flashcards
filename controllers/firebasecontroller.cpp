#include "firebasecontroller.h"

FirebaseController::FirebaseController(FirebaseService* firebaseService, QObject *parent)
    : QObject{parent}, m_firebaseService(firebaseService)
{
    connect(m_firebaseService, &FirebaseService::finished, this,
            [this](const QJsonDocument &doc, QString operationName) {

        if(operationName == "addNewSet"){
            emit addingSetCompleted();
        }
        if(operationName == "loadSets"){
            emit setsLoaded(doc);
        }


    });

    connect(m_firebaseService, &FirebaseService::error, this, [this](QString msg) {
        emit logout();
    });
}


void FirebaseController::testConnection(){
    m_firebaseService->sendGetRequest("https://firestore.googleapis.com/v1/projects/test-3eac3/databases/(default)/documents/TestTable", "TEST");


    connect(m_firebaseService, &FirebaseService::finished, this,
            [](const QJsonDocument& doc) {
                qDebug().noquote()
                << doc.toJson(QJsonDocument::Indented);
    });

    connect(m_firebaseService, &FirebaseService::error, this, [this](QString msg) {
        emit logout();
    });

}

void FirebaseController::loadSets() {

    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();
    QString userId = m_firebaseService->getUUID();

    QString url = QString(
        "https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets/"
        ).arg(projectId, userId);

    m_firebaseService->sendGetRequest(url, "loadSets");
}

void FirebaseController::saveSet(QString setId, QString setName, QList<CardObject> list){
    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();

    if(setId.isEmpty()){
        // ADDING NEW SET
        QString setId = QUuid::createUuid().toString(QUuid::WithoutBraces);
        QJsonObject setFields;
        QJsonObject setBody;
        QString timestamp = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

        setFields["name"] = QJsonObject{
            { "stringValue", setName }
        };

        setFields["count"] = QJsonObject{
            { "stringValue", QString::number(list.size()) }
        };

        setFields["createdAt"] = QJsonObject{
            { "timestampValue",
             timestamp }
        };

        setBody["fields"] = setFields;

        QString addSetUrl = QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets?documentId=%3")
                                .arg(projectId, m_firebaseService->getUUID(), setId);
        m_firebaseService->sendPostRequest(addSetUrl, setBody, "");

        // ADDING CARDS
        QJsonObject cardsBody = prepareCardsJsonBody(m_firebaseService->getUUID(), setId, list);
        QString addCardsUrl = QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents:commit").arg(projectId);
        m_firebaseService->sendPostRequest(addCardsUrl, cardsBody, "addNewSet");

    }else {
        // Aktualizujemy set
        qDebug() << "Aktualizuje set " << setName << "id:" << setId;
        for(int i = 0; i < list.size(); i++){

            qDebug() << list.at(i).getFront()
            << " "
            << list.at(i).getBack();

        }

    }
}

QJsonObject FirebaseController::prepareCardsJsonBody(QString uuid, QString setId, QList<CardObject> list) {
    QJsonObject cardsBody;
    QJsonArray writes;
    QString timestamp = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();

    for(int i = 0; i < list.size(); i++) {
        QString cardId = QUuid::createUuid().toString(QUuid::WithoutBraces);
        QJsonObject write;
        QJsonObject update;
        QJsonObject front;
        QJsonObject back;
        QJsonObject created;
        QJsonObject fields;
        QJsonObject precond;
        update.insert("name",
                      QString("projects/%1/databases/(default)/documents/users/%2/sets/%3/cards/%4")
                          .arg(projectId, m_firebaseService->getUUID(), setId, cardId));

        front.insert("stringValue", list.at(i).getFront());
        back.insert("stringValue", list.at(i).getBack());
        created.insert("timestampValue", timestamp);

        fields.insert("front", front);
        fields.insert("back", back);
        fields.insert("createdAt", created);

        update.insert("fields", fields);
        write.insert("update", update);

        precond.insert("exists", false);
        write.insert("currentDocument", precond);
        writes.append(write);
    }

    cardsBody.insert("writes", writes);
    return cardsBody;
}
