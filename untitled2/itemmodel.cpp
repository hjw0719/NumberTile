#include "itemmodel.h"
#include "util.h"
ItemModel::ItemModel()
{
    m_tRoles.insert(eTileNumber, "nNumber");
    m_tRoles.insert(eTileState, "eState");
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.count();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    int nIndex = index.row();
    if (m_model.count() <= nIndex)
    {
        return QVariant();
    }
    else
    {
        switch (role)
        {
        case eTileNumber:
            return m_model.at(nIndex).number;
        case eTileState:
            return m_model.at(nIndex).eState;
        default:
            return QVariant();
        }
    }
}

QHash<int, QByteArray> ItemModel::roleNames() const
{
    return m_tRoles;
}

void ItemModel::setList(QList<Tile> &tList)
{
    beginResetModel();
    m_model = tList;
    endResetModel();
}

Tile ItemModel::getData(const int nRow)
{
    if (m_model.count() <= nRow)
    {
        return Tile();
    }
    else
    {
        return m_model.at(nRow);
    }
}

void ItemModel::setItem(const Tile &tTile)
{
    if (!m_model.isEmpty())
    {
        tTile
    }
}
