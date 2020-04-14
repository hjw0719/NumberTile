#ifndef ITEMMODEL_H
#define ITEMMODEL_H
#include "util.h"
#include <QAbstractItemModel>
#include "qdebug.h"


class ItemModel : public QAbstractListModel
{
    Q_OBJECT
    enum eItemRoles
    {
        eTileNumber = 0,
        eTileState
    };

public:
    ItemModel();

public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int,QByteArray> roleNames() const;
    void setList(QList<Tile> &tList);

    Tile getData(const int nRow);
    void editItem(const int &nIndex, const Tile &tTile);
    QList<int> getVacancyIndexList();
private:
    QList<Tile> m_model;
    QHash<int,QByteArray> m_tRoles;

};

#endif // ITEMMODEL_H
