#include "itemmodel.h"
#include <QDebug>

ItemModel::ItemModel()
{
    m_tRoles.insert(eTileNumber, "nNumber");
    m_tRoles.insert(eTileState, "eState");
}

ItemModel::~ItemModel()
{
    qDeleteAll(m_model);
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
            return m_model.at(nIndex)->getNumber();
        case eTileState:
            return m_model.at(nIndex)->getTileState();
        default:
            return QVariant();
        }
    }
}

QHash<int, QByteArray> ItemModel::roleNames() const
{
    return m_tRoles;
}

void ItemModel::setList(QList<HTile *> &tList)
{
    beginResetModel();
    m_model = tList;
    endResetModel();
}

HTile *ItemModel::getData(const int nRow)
{
    if (m_model.count() <= nRow)
    {
        return nullptr;
    }
    else
    {
        return m_model.at(nRow);
    }
}

void ItemModel::editItem(const int &nIndex, const ETileState &eTileState, int nNumber)
{
    beginResetModel();
    qDebug() << Q_FUNC_INFO << nIndex;
    if (!m_model.isEmpty())
    {
        HTile *tile = m_model.at(nIndex);

        tile->setTileState(eTileState);
        tile->setNumber(nNumber);
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
        if (E_TILE_STATE_VACANCY == m_model.at(i)->getTileState())
        {
            tempList.append(i);
        }
    }

    return tempList;
}

int ItemModel::lastNumber()
{
    if (m_model.isEmpty())
    {
        return -1;
    }

    return m_model.last()->getNumber();
}

int ItemModel::firstNumber()
{
    if (m_model.isEmpty())
    {
        return -1;
    }

    return m_model.first()->getNumber();
}
