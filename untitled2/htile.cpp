#include "htile.h"

#include "hdatamanager.h"

HTile::HTile(QQuickItem *parent) :
    QQuickItem(parent),
    m_nNumber(0),
    m_eTileStatus(HEnum::E_TILE_STATUS_VACANCY)
{

}

HTile::~HTile()
{

}

void HTile::initialize()
{
    m_nNumber = 0;
    m_eTileStatus = HEnum::E_TILE_STATUS_VACANCY;
}

uint64_t HTile::getNumber() const
{
    return m_nNumber;
}

void HTile::setNumber(QVariant vNumber)
{
    if(vNumber.canConvert<uint64_t>())
    {
        m_nNumber = vNumber.value<uint64_t>();
    }
    else
    {
        qDebug() << "Can't convert !!";
    }

    emit numberChanged();
}

HEnum::ETileStatus HTile::getTileStatus() const
{
    return m_eTileStatus;
}

void HTile::setTileStatus(const QVariant &vState)
{
    if (vState.canConvert<HEnum::ETileStatus>())
    {
        m_eTileStatus = vState.value<HEnum::ETileStatus>();

        emit tileStatusChanged();
    }
    else
    {
        qDebug() << "Can't convert !!";
    }
}

void HTile::onSuccessTouched()
{
    HDataManager::instance()->touchProcess(HEnum::E_TOUCH_STATUS_SUCCESS);
}

void HTile::onFailTouched()
{
    HDataManager::instance()->touchProcess(HEnum::E_TOUCH_STATUS_FAIL);
}

