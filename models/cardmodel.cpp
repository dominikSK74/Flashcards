#include "cardmodel.h"
#include <QJsonObject>

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

void CardModel::loadCards(QJsonDocument doc) {
    QJsonObject rootObj = doc.object();

    beginResetModel();
    m_list.clear();

    QJsonArray documents = rootObj["documents"].toArray();

    for (const QJsonValue &docVal : documents) {
        QJsonObject docObj = docVal.toObject();
        QJsonObject fields = docObj["fields"].toObject();

        QString front = fields["front"].toObject()["stringValue"].toString();
        QString back = fields["back"].toObject()["stringValue"].toString();
        QString timestampString = fields["createdAt"].toObject()["timestampValue"].toString();

        QDateTime createdAt = QDateTime::fromString(timestampString, Qt::ISODate);
        createdAt.setTimeZone(QTimeZone::utc());
        int index = fields["index"].toObject()["stringValue"].toString().toInt();

        m_list.append(CardObject(front, back, createdAt, index));
    }

    std::sort(m_list.begin(), m_list.end(), [](const CardObject &a, const CardObject &b) {
        return a.getIndex() < b.getIndex();
    });

    endResetModel();
}

void CardModel::saveSet(QString id_set, QString setName, FirebaseController* firebaseController, QVariant data){
    QJsonDocument doc = data.value<QJsonDocument>();
    firebaseController->saveSet(id_set, setName, m_list, doc);
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

void CardModel::removeCard(int index){
    QList<CardObject> newList;

    for(int i = 0; i < m_list.size(); i++){
        if(i != index){
            newList.append(m_list[i]);
        }
    }
    beginResetModel();
    m_list.clear();
    m_list = newList;
    endResetModel();
}

void CardModel::importCardsFromCSV(QString filePath) {
    QUrl url(filePath);

    QFile file(url.toLocalFile());

    if (!file.exists()) {
        emit sendAlert("error", "Error: File does not exist at: " + url.toLocalFile());
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit sendAlert("error", "Error: Could not open file for reading.");
        return;
    }

    emit sendAlert("success", "Open file success!");

    QList<CardObject> cards;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Line:" << line;
        QList<QString> list = line.split(";");

        if(list.size() != 2){
            emit sendAlert("error", "Error: Bad format of file!");
            return;
        }

        CardObject card;
        card.setFront(list[0]);
        card.setBack(list[1]);
        cards.append(card);
    }
    file.close();
    beginResetModel();
    m_list.clear();
    m_list = cards;
    endResetModel();
    emit sendAlert("success", "The file has been imported correctly.");
}


QVariantMap CardModel::get(int row) const
{
    QVariantMap map;
    if (row < 0 || row >= m_list.size())
        return map;

    map.insert("front", m_list.at(row).getFront());
    map.insert("back", m_list.at(row).getBack());
    return map;
}

void CardModel::addCard(QString front, QString back){
    CardObject card;
    card.setFront(front);
    card.setBack(back);

    qDebug() << "Dodaje front: " << front << " back: " << back;

    beginInsertRows(QModelIndex(), m_list.count(), m_list.count());
    m_list.append(card);
    endInsertRows();
}





