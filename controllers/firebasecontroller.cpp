#include "firebasecontroller.h"

FirebaseController::FirebaseController(FirebaseService* firebaseService, QObject *parent)
    : QObject{parent}, m_firebaseService(firebaseService)
{}


void FirebaseController::testConnection(){
    m_firebaseService->sendGetRequest("https://firestore.googleapis.com/v1/projects/test-3eac3/databases/(default)/documents/TestTable");


    connect(m_firebaseService, &FirebaseService::finished, this,
            [](const QJsonDocument& doc) {
                qDebug().noquote()
                << doc.toJson(QJsonDocument::Indented);
    });

    connect(m_firebaseService, &FirebaseService::error, this, [this](QString msg) {
        emit logout();
    });

}

