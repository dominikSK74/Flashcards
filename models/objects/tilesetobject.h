#ifndef TILESETOBJECT_H
#define TILESETOBJECT_H

#include <QtCore>

class TileSetObject
{
public:
    TileSetObject();
    TileSetObject(QString name, int count, QString id, bool isAdd = false);
    void setName(QString name);
    QString getName();

    void setCount(int count);
    int getCount();

    void setId(QString id);
    QString getId();


    bool isSpecial();

private:
    QString id;
    QString name;
    int count;
    bool isAdd;
};

#endif // TILESETOBJECT_H
