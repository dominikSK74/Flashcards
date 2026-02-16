#include "cardobject.h"

CardObject::CardObject(): front(""), back("") {}

CardObject::CardObject(QString front, QString back) : front(front), back(back) {}

CardObject::CardObject(QString front, QString back, QString id) : front(front), back(back), id(id) {}

QString CardObject::getFront() { return front; }
QString CardObject::getFront() const { return front; }
void CardObject::setFront(QString front) { this->front = front; }

QString CardObject::getBack() { return back; }
QString CardObject::getBack() const { return back; }

void CardObject::setBack(QString back) { this->back = back; }

QString CardObject::getId() { return id; }
void CardObject::setId(QString id) { this->back = id; }
