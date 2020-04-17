#include "hdatamanager.h"

#include "htile.h"
#include "hgamer.h"
#include "HDefine.h"

#include <QTimer>

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent),
    m_bFever(false),
    m_nFeverGauge(0),
    m_nCombo(0),
    m_nScore(0)
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
        int addScore = getScore() + (getFever() ? FEVER_SCORE : DEFAULT_SCORE);
        setScore(addScore);

        // [2] Add Combo.
        setCombo(getCombo() + 1);

        emit updateUI(HEnum::E_UPDATE_UI_SUCCESS_TOUCH);

        // [3] Check Fever.
        if (COMBO_FOR_FEVER <= getFeverGauge())
        {
            setFever(true);
            setFeverGauge(0);
            emit updateUI(HEnum::E_UPDATE_UI_FEVER);

            QTimer::singleShot(FEVER_INTERVAL, this, [=](){
                setFever(false);
                emit updateUI(HEnum::E_UPDATE_UI_NORMAL);
            });
        }
    }   break;
    case HEnum::E_TOUCH_STATUS_FAIL :
    {
        // [1] init Combo.
        setCombo(0);

        emit updateUI(HEnum::E_UPDATE_UI_FAIL_TOUCH);
    }   break;
    default : break;
    }

    // update UI
}

void HDataManager::setScore(const qulonglong &nScore)
{
    m_nScore = nScore;
}

qulonglong HDataManager::getScore()
{
    return m_nScore;
}

void HDataManager::setCombo(const quint16 &nCombo)
{
    m_nCombo = nCombo;

    if (!getFever())
    {
        if (0 == m_nCombo)
        {
            setFeverGauge(0);
        }
        else
        {
            setFeverGauge(getFeverGauge() + 1);
        }
    }
}

quint16 HDataManager::getCombo()
{
    return m_nCombo;
}

void HDataManager::setFever(const bool &bFever)
{
    m_bFever = bFever;

    emit feverChanged(m_bFever);
}

bool HDataManager::getFever()
{
    return m_bFever;
}

void HDataManager::initialize()
{
    if (m_pCurrentGamer.isNull())
    {
        m_pCurrentGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
    }
}

quint8 HDataManager::getFeverGauge() const
{
    return m_nFeverGauge;
}

void HDataManager::setFeverGauge(const quint8 &nFeverGauge)
{
    m_nFeverGauge = nFeverGauge;
}
