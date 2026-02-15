#include "cardmodel.h"

CardModel::CardModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_roleNames[FrontRole] = "front";
    m_roleNames[BackRole] = "back";

    m_list.append(CardObject("", ""));
}

int CardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant CardModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if(row < 0 || row >= m_list.count()) {
        return QVariant();
    }

    switch(role) {
    case FrontRole:
        return m_list.value(row).getFront();
    case BackRole:
        return m_list.value(row).getBack();
    }

    return QVariant();
}


QHash<int, QByteArray> CardModel::roleNames() const
{
    return m_roleNames;
}
