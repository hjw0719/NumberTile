#include "hdatamanager.h"

#include "htile.h"
#include "hgamer.h"

#define TILE_COUNT 8

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent)
{
    initialize();
}

QSharedPointer<HDataManager> HDataManager::instance()
{
    if (obj.isNull())
    {
        obj = QSharedPointer<HDataManager>(new HDataManager, &HDataManager::doDelete);
    }

    return obj;
}

void HDataManager::doDelete(HDataManager *manager)
{
    if (nullptr != manager)
    {
        delete manager;
    }
}

void HDataManager::touchProcess(const ETouchStatus &eTouchStatus)
{
    if (m_pCurrentGamer.isNull())
    {
        return;
    }

    switch(eTouchStatus)
    {
    case E_TOUCH_STATUS_SUCCESS :
    {
        // [1] 점수 산정.

        m_pCurrentGamer->setScore(m_pCurrentGamer->getScore() + 100);

        // [2] 타이머 컨트롤.
        emit successTouched();
    }   break;
    case E_TOUCH_STATUS_FAIL :
    {
        // [1] 타이머 컨트롤.

        emit failedTouched();
    }   break;
    default : break;
    }
}

void HDataManager::initialize()
{
    m_pCurrentGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
}
