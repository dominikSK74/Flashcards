#include "tilesetmodel.h"

TileSetModel::TileSetModel(QObject *parent) : QAbstractListModel(parent) {

    m_roleNames[NameRole] = "name";
    m_roleNames[CountRole] = "count";
    m_roleNames[IsAddRole] = "isAdd";

    //TestData
    m_list.append(TileSetObject("Nazwa1", 10));
    m_list.append(TileSetObject("Nazwa2", 20));
    m_list.append(TileSetObject("Nazwa3", 33));
    m_list.append(TileSetObject("Nazwa4", 49));

    m_list.append(TileSetObject("Nazwa1", 10));
    m_list.append(TileSetObject("Nazwa1", 20));
    m_list.append(TileSetObject("Nazwa1", 33));
    m_list.append(TileSetObject("Nazwa1", 49));

    m_list.append(TileSetObject("Nazwa2", 10));
    m_list.append(TileSetObject("Nazwa2", 20));
    m_list.append(TileSetObject("Nazwa2", 33));
    m_list.append(TileSetObject("Nazwa2", 49));

    m_list.append(TileSetObject("Nazwa3", 10));
    m_list.append(TileSetObject("Nazwa3", 20));
    m_list.append(TileSetObject("Nazwa3", 33));
    m_list.append(TileSetObject("Nazwa3", 49));

    m_list.append(TileSetObject("Nazwa4", 10));
    m_list.append(TileSetObject("Nazwa4", 20));
    m_list.append(TileSetObject("Nazwa4", 33));
    m_list.append(TileSetObject("Nazwa4", 49));


    m_list.append(TileSetObject("", 0, true));
}

int TileSetModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant TileSetModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if(row < 0 || row >= m_list.count()) {
        return QVariant();
    }

    switch(role) {
    case NameRole:
        return m_list.value(row).getName();
    case CountRole:
        return m_list.value(row).getCount();
    case IsAddRole:
        return m_list.value(row).isSpecial();
    }

    return QVariant();
}


QHash<int, QByteArray> TileSetModel::roleNames() const
{
    return m_roleNames;
}
