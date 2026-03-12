#include "quizobject.h"

QuizObject::QuizObject() {

}

QuizObject::QuizObject(QString name, int count, QString id, QDateTime createdTime, bool isAdd)
    : name(name), count(count), id(id), isAdd(isAdd), createdTime(createdTime) {}

void QuizObject::setName(QString name) { this->name = name; }

QString QuizObject::getName() { return this->name; }

void QuizObject::setCount(int count) { this->count = count; }

int QuizObject::getCount() { return this->count; };

bool QuizObject::isSpecial() { return isAdd; }

void QuizObject::setId(QString id) { this->id = id; }
QString QuizObject::getId() { return id; }

QDateTime QuizObject::getCreatedTime() const { return createdTime; }
void QuizObject::setCreatedTime(QDateTime createdTime){ this->createdTime = createdTime; }
