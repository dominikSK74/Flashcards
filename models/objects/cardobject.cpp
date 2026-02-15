#include "cardobject.h"

CardObject::CardObject() {}

CardObject::CardObject(QString front, QString back) : front(front), back(back) {}

QString CardObject::getFront() { return front; }
void CardObject::setFront(QString front) { this->front = front; }

QString CardObject::getBack() { return back; }
void CardObject::setBack(QString back) { this->back = back; }
