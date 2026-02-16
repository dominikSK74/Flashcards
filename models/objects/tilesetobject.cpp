#include "tilesetobject.h"

TileSetObject::TileSetObject() {}

TileSetObject::TileSetObject(QString name, int count, QString id, bool isAdd) : name(name), count(count), id(id), isAdd(isAdd) {}

void TileSetObject::setName(QString name) { this->name = name; }

QString TileSetObject::getName() { return this->name; }

void TileSetObject::setCount(int count) { this->count = count; }

int TileSetObject::getCount() { return this->count; };

bool TileSetObject::isSpecial() { return isAdd; }

void TileSetObject::setId(QString id) { this->id = id; }
QString TileSetObject::getId() { return id; }
