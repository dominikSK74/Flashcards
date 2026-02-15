#ifndef CARDOBJECT_H
#define CARDOBJECT_H
#include <QtCore>

class CardObject
{
public:
    CardObject();
    CardObject(QString front, QString back);

    QString getFront();
    void setFront(QString front);

    QString getBack();
    void setBack(QString back);

private:
    QString front;
    QString back;
};

#endif // CARDOBJECT_H
