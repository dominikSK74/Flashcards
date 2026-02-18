#include "cardobject.h"

CardObject::CardObject(): front(""), back("") {}

CardObject::CardObject(QString front, QString back, QDateTime createdTime, int index)
    : front(front), back(back), createdTime(createdTime), index(index) {}

CardObject::CardObject(QString front, QString back, QString id, QDateTime createdTime, int index)
    : front(front), back(back), id(id), createdTime(createdTime), index(index) {}

QString CardObject::getFront() { return front; }
QString CardObject::getFront() const { return front; }
void CardObject::setFront(QString front) { this->front = front; }

QString CardObject::getBack() { return back; }
QString CardObject::getBack() const { return back; }

void CardObject::setBack(QString back) { this->back = back; }

QString CardObject::getId() { return id; }
void CardObject::setId(QString id) { this->back = id; }

QDateTime CardObject::getCreatedTime() const { return createdTime; }
void CardObject::setCreatedTime(QDateTime createdTime){ this->createdTime = createdTime; }

int CardObject::getIndex() const { return index; }
void CardObject::setIndex(int index) { this->index = index; }
