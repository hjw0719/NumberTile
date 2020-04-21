#include "hdatamanager.h"

#include "htile.h"
#include "hgamer.h"
#include "HDefine.h"
#include "hsettingmanager.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

#define DEMO_VERSION

QSharedPointer<HDataManager> obj = NULL;

HDataManager::HDataManager(QObject *parent) :
    QObject(parent),
    m_bFever(false),
    m_nFeverGauge(0),
    m_nCombo(0),
    m_nMaxCombo(0),
    m_nScore(0),
    m_nTileNumber(0)
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

        // [3] Check & Add Max Combo
        setMaxCombo(getCombo());

        // [4] Play Sound
        HSettingManager::instance()->setPlaySoundStatus(HEnum::E_SOUND_TILE_SUCCESS, true);

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

        HSettingManager::instance()->setPlaySoundStatus(HEnum::E_SOUND_TILE_FAIL, true);

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

uint64_t HDataManager::getTileNumber() const
{
    return m_nTileNumber;
}

void HDataManager::setTileNumber(const uint64_t &nTileNumber)
{
    m_nTileNumber = nTileNumber;
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

bool HDataManager::highScoreThan(const QSharedPointer<HGamer> &pGamer1, const QSharedPointer<HGamer> &pGamer2)
{
    uint64_t pGamer1Score = pGamer1->getMaxScore();
    uint64_t pGamer2Score = pGamer2->getMaxScore();


    if (pGamer1Score == pGamer2Score)
    {
        return pGamer1->getMaxTileNumber() > pGamer2->getMaxTileNumber();
    }
    else
    {
        return pGamer1Score > pGamer2Score;
    }
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
#ifdef DEMO_VERSION
    QSharedPointer<HGamer> pGamer = QSharedPointer<HGamer>(new HGamer, &HGamer::doDeleteLater);
    pGamer->setMaxCombo(getMaxCombo());
    pGamer->setMaxScore(getScore());
    pGamer->setMaxTileNumber(getTileNumber());

    m_tRankList.append(pGamer);

    qSort(m_tRankList.begin(), m_tRankList.end(), highScoreThan);

    for (int i = 0; i < m_tRankList.count(); i++)
    {
        QSharedPointer<HGamer> tGamer = m_tRankList.at(i);
        tGamer->setRank(i+1);
    }
#else
    m_pCurrentGamer->setMaxCombo(getMaxCombo());
    m_pCurrentGamer->setMaxScore(getScore());

#endif
}
