#ifndef CARDOBJECT_H
#define CARDOBJECT_H
#include <QtCore>

class CardObject
{
public:
    CardObject();
    CardObject(QString front, QString back, QDateTime createdTime, int index);
    CardObject(QString front, QString back, QString id, QDateTime createdTime, int index);

    QString getFront();
    void setFront(QString front);

    QString getBack();
    void setBack(QString back);

    QString getBack() const;
    QString getFront() const;

    QString getId();
    void setId(QString id);

    QDateTime getCreatedTime() const;
    void setCreatedTime(QDateTime createdTime);

    int getIndex() const;
    void setIndex(int index);

private:
    QString id;
    QString front;
    QString back;
    QDateTime createdTime;
    int index;
};

#endif // CARDOBJECT_H
