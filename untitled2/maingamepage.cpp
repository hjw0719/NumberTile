#include "maingamepage.h"

#include "hlaunchermanager.h"
#include "hdatamanager.h"
#include "HDefine.h"
#include <QMetaObject>

#define OBJNAME_TILELIST "id_tileList"
#define OBJNAME_LIFEGAUGE "id_lifeGauge"
#define OBJNAME_SCORE "id_score"
#define OBJNAME_GAMEOVERPOPUP "id_gamaOverPopup"
#define OBJNAME_READYCOUNT "id_readyCount"

MainGamePage::MainGamePage() :
    HPage(QUrl("qrc:/MainGamePage.qml")),
    m_pLifeTimer(new QTimer),
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

    connect(getComponent(OBJNAME_GAMEOVERPOPUP), SIGNAL(clickedRestartButton()), this, SLOT(onClickedRestartButton()));
    connect(getComponent(OBJNAME_GAMEOVERPOPUP), SIGNAL(clickedScoreBoardButton()), this, SLOT(onClickedScoreBoardButton()));

    QObject::connect(m_pLifeTimer, SIGNAL(timeout()), this, SLOT(onLifeTimeEnd()));

    getComponent(OBJNAME_LIFEGAUGE)->setProperty("maxGauge", LIFE_MAX_TIME);

    connect(getComponent(OBJNAME_READYCOUNT), SIGNAL(countOver()), this, SLOT(onReadyCountOver()));

    startReadyCount();
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
    getComponent(OBJNAME_SCORE)->setProperty("text", nScore);
}

void MainGamePage::setComboText(const quint16 &nCombo)
{
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("combo", nCombo);
}

void MainGamePage::setFeverMode(const bool &bFever)
{
    m_qml->setProperty("bFever", bFever);
}

void MainGamePage::gameOver()
{
    getComponent(OBJNAME_GAMEOVERPOPUP)->setProperty("strScore", HDataManager::instance()->getScore());
    getComponent(OBJNAME_GAMEOVERPOPUP)->setProperty("strMaxCombo", HDataManager::instance()->getMaxCombo());

    getComponent(OBJNAME_GAMEOVERPOPUP)->setVisible(true);
}

void MainGamePage::gameStart()
{
    setRemainGauge(LIFE_MAX_TIME);
    timerStart(LIFE_MAX_TIME);
}

void MainGamePage::timerStart(const int &nTime)
{
//    m_pLifeTimer->setSingleShot(true);
    m_pLifeTimer->start(nTime);
}

void MainGamePage::startReadyCount()
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_TILELIST), "initData", Qt::QueuedConnection);
    getComponent(OBJNAME_GAMEOVERPOPUP)->setVisible(false);
    setScoreText(0);
    setComboText(0);
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("currentPercent", 1);
    getComponent(OBJNAME_READYCOUNT)->setProperty("readyCountNumber", READY_COUNT_MAX);
}

void MainGamePage::onLifeTimeEnd()
{
    HDataManager::instance()->saveData();
    gameOver();

    HDataManager::instance()->dataInitialize();
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
    int nTempRemainTime = m_pLifeTimer->remainingTime() - LIFE_REDUCE_INTERVAL;
    qDebug() << Q_FUNC_INFO << m_pLifeTimer->remainingTime() << " " << LIFE_REDUCE_INTERVAL;
    if (LIFE_REDUCE_INTERVAL > nTempRemainTime)
    {
        nTempRemainTime = 0;
        gameOver();
        m_pLifeTimer->stop();
    }
    else
    {
        timerStart(nTempRemainTime);
    }

    setRemainGauge(nTempRemainTime);
}

void MainGamePage::addLifeTime()
{
    // 정확한 선택에 의한 life gage 증가.
    int nTempRemainTime = m_pLifeTimer->remainingTime() + m_nAddLifeTimeInterval;
    qDebug() << Q_FUNC_INFO << m_pLifeTimer->remainingTime() << " " << m_nAddLifeTimeInterval;

    if (LIFE_MAX_TIME <= nTempRemainTime)
    {
        nTempRemainTime = LIFE_MAX_TIME;
    }
    setRemainGauge(nTempRemainTime);
    m_pLifeTimer->stop();
    timerStart(nTempRemainTime);
    reduceAddtimeInterval();
}

void MainGamePage::onClickedRestartButton()
{
    qDebug() << Q_FUNC_INFO;

    m_nAddLifeTimeInterval = LIFE_ADD_INTERVAL_INIT;
    startReadyCount();
}

void MainGamePage::onClickedScoreBoardButton()
{
    qDebug() << Q_FUNC_INFO;
    HLauncherManager::instance()->pageTransition(HEnum::E_PAGE_SCORE_BOARD, HEnum::E_TRANSITION_SHOW_ALL_CLEAR);

}

void MainGamePage::onReadyCountOver()
{
    qDebug() << Q_FUNC_INFO;
    gameStart();
}
