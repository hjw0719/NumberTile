#include "htile.h"

#include "hdatamanager.h"

HTile::HTile(QQuickItem *parent) :
    QQuickItem(parent),
    m_nNumber(0),
    m_eTileStatus(E_TILE_STATUS_VACANCY)
{

}

HTile::~HTile()
{

}

void HTile::initialize()
{
    m_nNumber = 0;
    m_eTileStatus = E_TILE_STATUS_VACANCY;
}

quint64 HTile::getNumber() const
{
    return m_nNumber;
}

void HTile::setNumber(QVariant vNumber)
{
    if(vNumber.canConvert<quint64>())
    {
        m_nNumber = vNumber.value<quint64>();
    }
    else
    {
        qDebug() << "Can't convert !!";
    }

    emit numberChanged();
}

HTile::ETileStatus HTile::getTileStatus() const
{
    return m_eTileStatus;
}

void HTile::setTileStatus(const QVariant &vState)
{
    if (vState.canConvert<HTile::ETileStatus>())
    {
        m_eTileStatus = vState.value<HTile::ETileStatus>();

        emit tileStatusChanged();
    }
    else
    {
        qDebug() << "Can't convert !!";
    }
}

void HTile::onSuccessTouched()
{
    HDataManager::instance()->touchProcess(HDataManager::E_TOUCH_STATUS_SUCCESS);
}

void HTile::onFailTouched()
{
    HDataManager::instance()->touchProcess(HDataManager::E_TOUCH_STATUS_FAIL);
}

