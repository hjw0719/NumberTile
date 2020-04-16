#include "hdatamanager.h"

#include "htile.h"
#include "hgamer.h"
#include "HDefine.h"

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent)
{
    initialize();
}

HDataManager *HDataManager::instance()
{
    if (obj.isNull())
    {
        obj = QSharedPointer<HDataManager>(new HDataManager, &HDataManager::doDelete);
    }

    return obj.data();
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
        // [1] Add Score.
        m_pCurrentGamer->setScore(m_pCurrentGamer->getScore() + DEFAULT_SCORE);

        // [2] Add Combo.
        m_pCurrentGamer->setCombo(m_pCurrentGamer->getCombo() + 1);

        // [3] Control Timer.
        emit successTouched();
    }   break;
    case E_TOUCH_STATUS_FAIL :
    {
        // [1] init Combo.
        m_pCurrentGamer->setCombo(0);

        // [2] Contorl Timer
        emit failedTouched();
    }   break;
    default : break;
    }
}

void HDataManager::initialize()
{
    m_pCurrentGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
}
