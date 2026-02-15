#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QAbstractListModel>
#include "objects/cardobject.h"

class CardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CardModel(QObject *parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    enum RoleNames {
        FrontRole = Qt::UserRole+1,
        BackRole = Qt::UserRole+2,
    };

private:
    QList<CardObject> m_list;
    QHash<int, QByteArray> m_roleNames;
};

#endif // CARDMODEL_H
