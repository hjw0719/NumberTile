#include "maingamepage.h"

#include "hdatamanager.h"
#include "HDefine.h"
#include <QMetaObject>

#define OBJNAME_TILELIST "id_tileList"
#define OBJNAME_LIFEGAUGE "id_lifeGauge"


MainGamePage::MainGamePage() :
    HPage(QUrl("qrc:/MainGamePage.qml")),
    m_nAddLifeTimeInterval(LIFE_ADD_INTERVAL_INIT)
{
    initialize();
}

MainGamePage::~MainGamePage()
{

}

void MainGamePage::initialize()
{
    HPage::initialize();

    connect(HDataManager::instance(), SIGNAL(updateUI(HEnum::EUpdateUIType)), this, SLOT(onUpdateUI(HEnum::EUpdateUIType)));
    m_LifeTimer.setSingleShot(true);
    m_LifeTimer.start(LIFE_MAX_TIME);
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("maxGauge", LIFE_MAX_TIME);
    setRemainGauge(LIFE_MAX_TIME);
}

void MainGamePage::reduceAddtimeInterval()
{
    // 타일 터치시 life gage의 증가폭을 감소시킴(단계가 올라갈수록 난이도 증가를 위한 장치).
    if (LIFE_ADD_INTERVAL_MIN == m_nAddLifeTimeInterval)
    {
        return;
    }
    int tempInterval = m_nAddLifeTimeInterval - LIFE_ADD_INTERVAL_REDUCE_SIZE;
    if (tempInterval < LIFE_ADD_INTERVAL_MIN)
    {
        tempInterval = LIFE_ADD_INTERVAL_MIN;
    }

    m_nAddLifeTimeInterval = tempInterval;
}

void MainGamePage::setRemainGauge(int nRemainGauge)
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "setRemainGauge", Qt::QueuedConnection, Q_ARG(QVariant, nRemainGauge));
}

void MainGamePage::setScoreText(const qulonglong &nScore)
{
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("score", nScore);
}

void MainGamePage::setComboText(const quint16 &nCombo)
{
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("combo", nCombo);
}

void MainGamePage::setFeverMode(const bool &bFever)
{
    m_qml->setProperty("bFever", bFever);
}

void MainGamePage::onUpdateUI(HEnum::EUpdateUIType eUpdateUIType)
{
    switch(eUpdateUIType)
    {
    case HEnum::E_UPDATE_UI_SUCCESS_TOUCH :
    {
        // [1] Control Timer.
        addLifeTime();

        // [2] Update Score.
        setScoreText(HDataManager::instance()->getScore());

        // [3] Update combo.
        setComboText(HDataManager::instance()->getCombo());
    }   break;
    case HEnum::E_UPDATE_UI_FAIL_TOUCH :
    {
        // [1] Control Timer.
        reduceLifeTime();

        // [2] Update Combo.
        setComboText(HDataManager::instance()->getCombo());
    }   break;
    case HEnum::E_UPDATE_UI_FEVER :
    {
        setFeverMode(true);
    }   break;
    case HEnum::E_UPDATE_UI_NORMAL :
    {
        setFeverMode(false);
    }   break;
    default : break;
    }
}

void MainGamePage::reduceLifeTime()
{
    // 잘못된 선택에 의한 life gage 감소.
    int nTempRemainTime = m_LifeTimer.remainingTime() - LIFE_REDUCE_INTERVAL;
    qDebug() << Q_FUNC_INFO << m_LifeTimer.remainingTime() << " " << LIFE_REDUCE_INTERVAL;
    if (LIFE_REDUCE_INTERVAL > nTempRemainTime)
    {
        nTempRemainTime = 0;
    }
    setRemainGauge(nTempRemainTime);
    m_LifeTimer.stop();
    m_LifeTimer.start(nTempRemainTime);
}

void MainGamePage::addLifeTime()
{
    // 정확한 선택에 의한 life gage 증가.
    int nTempRemainTime = m_LifeTimer.remainingTime() + m_nAddLifeTimeInterval;
    qDebug() << Q_FUNC_INFO << m_LifeTimer.remainingTime() << " " << m_nAddLifeTimeInterval;

    if (LIFE_MAX_TIME <= nTempRemainTime)
    {
        nTempRemainTime = LIFE_MAX_TIME;
    }
    setRemainGauge(nTempRemainTime);
    m_LifeTimer.stop();
    m_LifeTimer.start(nTempRemainTime);
    reduceAddtimeInterval();
}
