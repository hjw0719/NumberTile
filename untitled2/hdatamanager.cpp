#include "hdatamanager.h"

#include "htile.h"
#include "hgamer.h"
#include "HDefine.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent),
    m_bFever(false),
    m_nFeverGauge(0),
    m_nCombo(0),
    m_nMaxCombo(0),
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
    switch(eTouchStatus)
    {
    case HEnum::E_TOUCH_STATUS_SUCCESS :
    {
        // [1] Add Score.
        int addScore = getScore() + (getFever() ? FEVER_SCORE : DEFAULT_SCORE);
        setScore(addScore);

        // [2] Add Combo.
        setCombo(getCombo() + 1);

        // [3] Check & Add Max Combo;
        setMaxCombo(getCombo());

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

void HDataManager::setScore(const uint64_t &nScore)
{
    m_nScore = nScore;
}

uint64_t HDataManager::getScore()
{
    return m_nScore;
}

void HDataManager::setCombo(const uint16_t &nCombo)
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

uint16_t HDataManager::getCombo()
{
    return m_nCombo;
}

void HDataManager::setMaxCombo(const uint16_t &nMaxCombo)
{
    if (m_nMaxCombo < nMaxCombo)
    {
        m_nMaxCombo = nMaxCombo;
    }
}

uint16_t HDataManager::getMaxCombo()
{
    return m_nMaxCombo;
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
//    if (m_pCurrentGamer.isNull())
//    {
//        m_pCurrentGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
    //    }
}

void HDataManager::calculateRank(QSharedPointer<HGamer> pGamer)
{
    if(m_tRankList.isEmpty())
    {
        pGamer->setRank(1);
    }
    else
    {
        pGamer->setRank(2);
    }
}

QJsonArray HDataManager::convertRankListToJsonArray()
{
    QJsonArray array;
    for (int i= 0 ; i < m_tRankList.count(); i++)
    {
        QSharedPointer<HGamer> pGamer = m_tRankList.at(i);
        if (!pGamer.isNull())
        {
            array.append(pGamer->toJson());
        }
    }

    return array;
}

uint8_t HDataManager::getFeverGauge() const
{
    return m_nFeverGauge;
}

void HDataManager::setFeverGauge(const uint8_t &nFeverGauge)
{
    m_nFeverGauge = nFeverGauge;
}

void HDataManager::dataInitialize()
{
    m_bFever = false;
    m_nCombo = 0;
    m_nMaxCombo =0;
    m_nScore = 0;
    m_nFeverGauge = 0;
}

void HDataManager::saveData()
{
    QSharedPointer<HGamer> pGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
    pGamer->setMaxCombo(getMaxCombo());
    pGamer->setMaxScore(getScore());

    calculateRank(pGamer);

    m_tRankList.append(pGamer);
}
