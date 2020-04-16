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

    connect(HDataManager::instance(), SIGNAL(successTouched()), this, SLOT(addLifeTime()));
    connect(HDataManager::instance(), SIGNAL(failedTouched()), this, SLOT(reduceLifeTime()));
    m_LifeTimer.setSingleShot(true);
    m_LifeTimer.start(LIFE_MAX_TIME);
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
        m_nAddLifeTimeInterval = LIFE_ADD_INTERVAL_MIN;
    }
}

void MainGamePage::setRemainGauge(int nRemainGauge)
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "setRemainGauge", Qt::QueuedConnection, Q_ARG(QVariant, nRemainGauge));
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
