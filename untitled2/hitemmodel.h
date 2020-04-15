#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractItemModel>
#include "htile.h"

class HItemModel : public QAbstractListModel
{
    Q_OBJECT
    enum eItemRoles
    {
        eTileNumber = 0,
        eTileState
    };

public:
    explicit HItemModel();
    virtual ~HItemModel();


public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int,QByteArray> roleNames() const;
    void setList(QList<HTile *> &tList);

    HTile *getData(const int nRow);
    void editItem(const int &nIndex, const HTile::ETileState &eTileState, int nNumber);
    QList<int> getVacancyIndexList();

    int lastNumber();
    int firstNumber();
private:
    QList<HTile *> m_model;
    QHash<int,QByteArray> m_tRoles;

};

#endif // ITEMMODEL_H
