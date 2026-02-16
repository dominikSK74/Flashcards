#ifndef CARDOBJECT_H
#define CARDOBJECT_H
#include <QtCore>

class CardObject
{
public:
    CardObject();
    CardObject(QString front, QString back);
    CardObject(QString front, QString back, QString id);

    QString getFront();
    void setFront(QString front);

    QString getBack();
    void setBack(QString back);

    QString getBack() const;
    QString getFront() const;

    QString getId();
    void setId(QString id);

private:
    QString id;
    QString front;
    QString back;
};

#endif // CARDOBJECT_H
