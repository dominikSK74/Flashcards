#include "tilesetobject.h"

TileSetObject::TileSetObject() {}

TileSetObject::TileSetObject(QString name, int count, bool isAdd) : name(name), count(count), isAdd(isAdd) {}

void TileSetObject::setName(QString name) { this->name = name; }

QString TileSetObject::getName() { return this->name; }

void TileSetObject::setCount(int count) { this->count = count; }

int TileSetObject::getCount() { return this->count; };

bool TileSetObject::isSpecial() { return isAdd; }
