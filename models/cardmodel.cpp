#include "cardmodel.h"

CardModel::CardModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_roleNames[FrontRole] = "front";
    m_roleNames[BackRole] = "back";
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

void CardModel::addEmptyCard() {
    beginInsertRows(QModelIndex(), m_list.count(), m_list.count());
    m_list.append(CardObject());
    endInsertRows();
}

void CardModel::loadCardsFromDatabase(QString id_set) {

    // ZAPYTANIE DO BAZY O ID SET, TOKEN JEST W SESSION
    qDebug() << "Pobieram dane dla zestawu o id: " << id_set;

    //Fake data

    beginResetModel();
    m_list.clear();

    m_list.append(CardObject("test1", "test2"));
    m_list.append(CardObject("test2", "test2"));
    m_list.append(CardObject("test3", "test2"));
    m_list.append(CardObject("test4", "test2"));
    m_list.append(CardObject("test5", "test2"));
    m_list.append(CardObject("test6", "test2"));
    m_list.append(CardObject("test7", "test2"));

    endResetModel();

}

void CardModel::saveSet(QString id_set, QString setName){

    if(id_set.isEmpty()){
        // Nowy set
        qDebug() << "Dodaje nowy set " << setName;
        for(int i = 0; i < m_list.size(); i++){

            qDebug() << m_list.at(i).getFront()
            << " "
            << m_list.at(i).getBack();

        }

    }else {
        // Aktualizujemy set
        qDebug() << "Aktualizuje set " << setName << "id:" << id_set;
        for(int i = 0; i < m_list.size(); i++){

            qDebug() << m_list.at(i).getFront()
            << " "
            << m_list.at(i).getBack();

        }

        //TODO: aktualizacja qml->cpp
    }

}


Qt::ItemFlags CardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled
           | Qt::ItemIsSelectable
           | Qt::ItemIsEditable;
}


bool CardModel::setData(const QModelIndex &index,
                        const QVariant &value,
                        int role)
{
    if (!index.isValid())
        return false;

    auto &card = m_list[index.row()];

    switch (role) {
    case FrontRole:
        card.setFront(value.toString());
        break;
    case BackRole:
        card.setBack(value.toString());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, { role });
    return true;
}

