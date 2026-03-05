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
        if(operationName == "loadCards"){
            emit cardsLoaded(doc);
        }
        if(operationName == "deleteSet"){
            emit deleteSetCompleted();
        }
        if(operationName == "downloadCards"){
            emit deleteCardsLoaded(doc);
        }
        if(operationName == "deleteCardsDone"){
            emit deleteCardsDone();
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

void FirebaseController::saveSet(QString setId, QString setName, QList<CardObject> list, QJsonDocument doc){
    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();

    if(setId.isEmpty()){
        // ADDING NEW SET
        QString setId = QUuid::createUuid().toString(QUuid::WithoutBraces);
        QJsonObject setFields;
        QJsonObject setBody;


        setFields["name"] = QJsonObject{
            { "stringValue", setName }
        };

        setFields["count"] = QJsonObject{
            { "stringValue", QString::number(list.size()) }
        };

        setFields["createdAt"] = QJsonObject{
            { "timestampValue",
             QDateTime::currentDateTimeUtc().toString(Qt::ISODate) }
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
        //DELETING
        QJsonObject deleteBody = prepareDeleteCardsJsonBody(doc);
        QString deleteUrl = QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents:commit").arg(projectId);
        m_firebaseService->sendPostRequest(deleteUrl, deleteBody, "");

        //PATCH SETNAME
        QJsonObject setNameFields;
        QJsonObject setNameBody;
        setNameFields.insert("name", QJsonObject{{ "stringValue", setName }});
        setNameFields.insert("count", QJsonObject{{ "stringValue", QString::number(list.size()) }});
        setNameBody.insert("fields", setNameFields);

        QString url = QString(
                          "https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets/%3?updateMask.fieldPaths=name&updateMask.fieldPaths=count"
                          ).arg(projectId, m_firebaseService->getUUID(), setId);

        m_firebaseService->sendPatchRequest(url, setNameBody, "");

        //ADDING
        QJsonObject cardsBody = prepareCardsJsonBody(m_firebaseService->getUUID(), setId, list);
        QString addCardsUrl = QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents:commit").arg(projectId);
        m_firebaseService->sendPostRequest(addCardsUrl, cardsBody, "addNewSet");
    }
}

QJsonObject FirebaseController::prepareCardsJsonBody(QString uuid, QString setId, QList<CardObject> list) {
    QJsonObject cardsBody;
    QJsonArray writes;
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
        QJsonObject index;

        update.insert("name",
                      QString("projects/%1/databases/(default)/documents/users/%2/sets/%3/cards/%4")
                          .arg(projectId, m_firebaseService->getUUID(), setId, cardId));

        front.insert("stringValue", list.at(i).getFront());
        back.insert("stringValue", list.at(i).getBack());
        created.insert("timestampValue", QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
        index.insert("stringValue", QString::number(i));

        fields.insert("front", front);
        fields.insert("back", back);
        fields.insert("index", index);
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

void FirebaseController::loadCards(QString setId) {

    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();
    QString userUuid = m_firebaseService->getUUID();


    QString url = QString(
        "https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets/%3/cards"
        ).arg(projectId, userUuid, setId);

    m_firebaseService->sendGetRequest(url, "loadCards");
}

QJsonObject FirebaseController::prepareDeleteCardsJsonBody(QJsonDocument doc){
    QJsonObject body;
    QJsonArray writes;

    QJsonObject rootObj = doc.object();
    QJsonArray documents = rootObj["documents"].toArray();

    for (const QJsonValue &docVal : documents) {
        QJsonObject docObj = docVal.toObject();

        QString documentName = docObj["name"].toString();

        if (documentName.isEmpty())
            continue;

        QJsonObject write;
        write.insert("delete", documentName);
        writes.append(write);
    }

    body.insert("writes", writes);
    return body;
}

void FirebaseController::deleteSet(QString setId) {
    QSettings settings(":config.ini", QSettings::IniFormat);
    QString projectId = settings.value("firebaseProjectId").toString();
    QString userUuid = m_firebaseService->getUUID();

    // DOWNLOAD CARDS FROM SET
    QString url = QString(
                      "https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets/%3/cards"
                      ).arg(projectId, userUuid, setId);

    m_firebaseService->sendGetRequest(url, "downloadCards");

    // DELETE CARDS
    connect(this, &FirebaseController::deleteCardsLoaded, this, [this, projectId](const QJsonDocument& doc) {
        QJsonObject deleteBody = prepareDeleteCardsJsonBody(doc);
        QString deleteUrl = QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents:commit").arg(projectId);
        m_firebaseService->sendPostRequest(deleteUrl, deleteBody, "deleteCardsDone");
    });

    // DELETE SET
    connect(this, &FirebaseController::deleteCardsDone, this, [this, projectId, setId]() {

        QString url = QString(
            "https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/users/%2/sets/%3"
            ).arg(projectId, m_firebaseService->getUUID(), setId);

        m_firebaseService->sendDeleteRequest(url, "deleteSet");
    });
}
