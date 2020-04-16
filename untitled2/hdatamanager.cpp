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

void HDataManager::touchProcess(const HEnum::ETouchStatus &eTouchStatus)
{
    if (m_pCurrentGamer.isNull())
    {
        return;
    }

    switch(eTouchStatus)
    {
    case HEnum::E_TOUCH_STATUS_SUCCESS :
    {
        // [1] Add Score.
        m_pCurrentGamer->setScore(m_pCurrentGamer->getScore() + DEFAULT_SCORE);

        // [2] Add Combo.
        m_pCurrentGamer->setCombo(m_pCurrentGamer->getCombo() + 1);
    }   break;
    case HEnum::E_TOUCH_STATUS_FAIL :
    {
        // [1] init Combo.
        m_pCurrentGamer->setCombo(0);
    }   break;
    default : break;
    }

    // update UI
    emit updateUI(eTouchStatus);
}

qulonglong HDataManager::getScore()
{
    if (!m_pCurrentGamer.isNull())
    {
        return m_pCurrentGamer->getScore();
    }

    return 0;
}

quint16 HDataManager::getCombo()
{
    if (!m_pCurrentGamer.isNull())
    {
        return m_pCurrentGamer->getCombo();
    }

    return 0;
}

void HDataManager::initialize()
{
    if (m_pCurrentGamer.isNull())
    {
        m_pCurrentGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
    }
}
