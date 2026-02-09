#ifndef FIREBASECONTROLLER_H
#define FIREBASECONTROLLER_H

#include <QObject>
#include <services/firebaseservice.h>

class FirebaseController : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseController(FirebaseService* firebaseService, QObject *parent = nullptr);
    Q_INVOKABLE void testConnection();
signals:
    void logout();

private:
    FirebaseService* m_firebaseService;
};

#endif // FIREBASECONTROLLER_H
