#include "tilesetmodel.h"

TileSetModel::TileSetModel(QObject *parent) : QAbstractListModel(parent) {

    m_roleNames[NameRole] = "name";
    m_roleNames[CountRole] = "count";
    m_roleNames[IsAddRole] = "isAdd";
    m_roleNames[IdRole] = "id";
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
    case IdRole:
        return m_list.value(row).getId();
    }

    return QVariant();
}


QHash<int, QByteArray> TileSetModel::roleNames() const
{
    return m_roleNames;
}

void TileSetModel::loadData(const QJsonDocument &data) {
    QJsonObject root = data.object();
    QJsonArray documents = root["documents"].toArray();

    beginResetModel();
    m_list.clear();

    for (const QJsonValue& value : documents) {
        QJsonObject doc = value.toObject();
        QJsonObject fields = doc["fields"].toObject();

        QString setName = fields["name"].toObject()["stringValue"].toString();
        int count = fields["count"].toObject()["stringValue"].toString().toInt();
        QString setId = doc["name"].toString().split("/").last();

        m_list.append(TileSetObject(setName, count, setId));
    }

    m_list.append(TileSetObject("", 0, "", true));
    endResetModel();
}


