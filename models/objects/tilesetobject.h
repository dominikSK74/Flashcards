#ifndef TILESETOBJECT_H
#define TILESETOBJECT_H

#include <QtCore>

class TileSetObject
{
public:
    TileSetObject();
    TileSetObject(QString name, int count, bool isAdd = false);
    void setName(QString name);
    QString getName();

    void setCount(int count);
    int getCount();

    bool isSpecial();

private:
    QString name;
    int count;
    bool isAdd;
};

#endif // TILESETOBJECT_H
