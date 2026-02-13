#ifndef TILESETMODEL_H
#define TILESETMODEL_H

#include <QtCore>
#include "objects/tilesetobject.h"

class TileSetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TileSetModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    enum RoleNames {
        NameRole = Qt::UserRole+1,
        CountRole = Qt::UserRole+2,
        IsAddRole = Qt::UserRole +3,
    };

private:
    QList<TileSetObject> m_list;
    QHash<int, QByteArray> m_roleNames;
};

#endif // TILESETMODEL_H
