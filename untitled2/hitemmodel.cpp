#include "hitemmodel.h"
#include <QDebug>

HItemModel::HItemModel()
{
    m_tRoles.insert(eTileNumber, "nNumber");
    m_tRoles.insert(eTileState, "eState");
}

HItemModel::~HItemModel()
{
    qDeleteAll(m_model);
}

int HItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.count();
}

QVariant HItemModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> HItemModel::roleNames() const
{
    return m_tRoles;
}

void HItemModel::setList(QList<HTile *> &tList)
{
    beginResetModel();
    m_model = tList;
    endResetModel();
}

HTile *HItemModel::getData(const int nRow)
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

void HItemModel::editItem(const int &nIndex, const HTile::ETileState &eTileState, int nNumber)
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

QList<int> HItemModel::getVacancyIndexList()
{
    QList<int> tempList;
    tempList.clear();

    for (int i = 0; i < m_model.size() ; i++)
    {
        if (HTile::E_TILE_STATE_VACANCY == m_model.at(i)->getTileState())
        {
            tempList.append(i);
        }
    }

    return tempList;
}

int HItemModel::lastNumber()
{
    if (m_model.isEmpty())
    {
        return -1;
    }

    return m_model.last()->getNumber();
}

int HItemModel::firstNumber()
{
    if (m_model.isEmpty())
    {
        return -1;
    }

    return m_model.first()->getNumber();
}
