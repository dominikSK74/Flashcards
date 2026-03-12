#ifndef QUIZMODEL_H
#define QUIZMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "objects/quizobject.h"

class QuizModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QuizModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    enum RoleNames {
        NameRole = Qt::UserRole+1,
        CountRole = Qt::UserRole+2,
        IsAddRole = Qt::UserRole +3,
        IdRole = Qt::UserRole + 4,
    };

    Q_INVOKABLE void loadData(const QJsonDocument &data);

private:
    QList<QuizObject> m_list;
    QHash<int, QByteArray> m_roleNames;
};

#endif // QUIZMODEL_H
