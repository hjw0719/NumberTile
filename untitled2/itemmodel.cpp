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

void ItemModel::editItem(const int &nIndex, const Tile &tTile)
{
    beginResetModel();
    qDebug() << Q_FUNC_INFO << nIndex;
    if (!m_model.isEmpty())
    {

        qDebug() << Q_FUNC_INFO << "tTile.number : " << tTile.number;
        m_model.replace(nIndex, tTile);
    }
    endResetModel();
    emit dataChanged(index(nIndex,0),index(nIndex,0));
}

QList<int> ItemModel::getVacancyIndexList()
{
    QList<int> tempList;
    tempList.clear();

    for (int i = 0; i < m_model.size() ; i++)
    {
        if (vacancy == m_model.at(i).eState)
        {
            tempList.append(i);
        }
    }

    return tempList;
}
