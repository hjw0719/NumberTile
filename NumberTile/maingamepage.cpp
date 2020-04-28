#include "maingamepage.h"

#include "hlaunchermanager.h"
#include "hdatamanager.h"
#include "HDefine.h"
#include <QMetaObject>
#include "hwindow.h"

#define OBJNAME_TILELIST "id_tileList"
#define OBJNAME_LIFEGAUGE "id_lifeGauge"
#define OBJNAME_SCORE "id_score"
#define OBJNAME_GAMEOVERPOPUP "id_gamaOverPopup"
#define OBJNAME_READYCOUNT "id_readyCount"
#define OBJNAME_PAUSEPOPUP "id_pausePopup"
#define OBJNAME_PAUSEBUTTON "id_pauseButton"
#define OBJNAME_COMBO "id_combo"

MainGamePage::MainGamePage() :
    HPage(QUrl("qrc:/MainGamePage.qml")),
//    m_pLifeTimer(new QTimer),
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
    getComponent(OBJNAME_LIFEGAUGE)->setProperty("maxGauge", LIFE_MAX_TIME);

    connect(HDataManager::instance(),               SIGNAL(updateUI(HEnum::EUpdateUIType)), this,   SLOT(onUpdateUI(HEnum::EUpdateUIType)));
    connect(getComponent(OBJNAME_GAMEOVERPOPUP),    SIGNAL(clickedRestartButton()),         this,   SLOT(onClickedRestartButton()));
    connect(getComponent(OBJNAME_GAMEOVERPOPUP),    SIGNAL(clickedScoreBoardButton()),      this,   SLOT(onClickedScoreBoardButton()));
    connect(getComponent(OBJNAME_LIFEGAUGE),        SIGNAL(timeOver()),                     this,   SLOT(onLifeTimeEnd()));
    connect(getComponent(OBJNAME_READYCOUNT),       SIGNAL(countOver()),                    this,   SLOT(onReadyCountOver()));
    connect(getComponent(OBJNAME_PAUSEBUTTON),      SIGNAL(clicked()),                      this,   SLOT(onPauseButton()));
    connect(getComponent(OBJNAME_PAUSEPOPUP),       SIGNAL(clickedResumed()),               this,   SLOT(onClickedResumeButton()));
    connect(getComponent(OBJNAME_PAUSEPOPUP),       SIGNAL(clickedSettingButton()),         this,   SLOT(onClickedSettingButton()));
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
    //gauge의 남은시간을 조정하는 함수로 running 상태를 해당함수로 바꿀수는 없다.
    qDebug() << Q_FUNC_INFO << nRemainGauge;
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "setRemainGauge", Qt::DirectConnection, Q_ARG(QVariant, nRemainGauge));
}

void MainGamePage::setScoreText(const uint64_t &nScore)
{
    getComponent(OBJNAME_SCORE)->setProperty("text", nScore);
}

void MainGamePage::setComboText(const uint16_t &nCombo)
{
    getComponent(OBJNAME_COMBO)->setProperty("combo", nCombo);
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

    QEvent *releaseEvent = new QEvent(QEvent::MouseButtonRelease);
    QCoreApplication::postEvent(window(), releaseEvent);
}

void MainGamePage::gameStart()
{
//    setRemainGauge(LIFE_MAX_TIME);
//    timerStart();
}

void MainGamePage::timerStart()
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "timerStart", Qt::DirectConnection);
}

void MainGamePage::timerPaused()
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "timerPaused", Qt::DirectConnection);
}

void MainGamePage::timerStop()
{
    QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "timerStop", Qt::DirectConnection);
}

qreal MainGamePage::getRemainingTime()
{
   QVariant nRemaining = 0;
   QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "getRemainingTime", Qt::DirectConnection, Q_RETURN_ARG(QVariant, nRemaining));

   return nRemaining.toReal();
}

bool MainGamePage::getisTimerRunning()
{
    QVariant bIsTimerRunning = false;
    bool bSuccess = false;
    bSuccess = QMetaObject::invokeMethod(getComponent(OBJNAME_LIFEGAUGE), "getIsTimerRunning", Qt::DirectConnection, Q_RETURN_ARG(QVariant, bIsTimerRunning));
    qDebug() << Q_FUNC_INFO << bSuccess;
    return bIsTimerRunning.toBool();
}

void MainGamePage::startReadyCount(bool bInit)
{
    if (bInit)
    {
        QMetaObject::invokeMethod(getComponent(OBJNAME_TILELIST), "initData", Qt::DirectConnection);
        getComponent(OBJNAME_GAMEOVERPOPUP)->setVisible(false);
        setScoreText(0);
        setComboText(0);
        getComponent(OBJNAME_LIFEGAUGE)->setProperty("currentPercent", 1);
        setRemainGauge(LIFE_MAX_TIME);
    }
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
    qDebug() << Q_FUNC_INFO << getisTimerRunning();
    if (!getisTimerRunning())
    {
        return;
    }

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
    int nTempRemainTime = getRemainingTime() - LIFE_REDUCE_INTERVAL;
    qDebug() << Q_FUNC_INFO << getRemainingTime() << " " << LIFE_REDUCE_INTERVAL;

    if (LIFE_REDUCE_INTERVAL > nTempRemainTime)
    {
        setRemainGauge(0);
        timerStop();
//        onLifeTimeEnd();
    }
    else
    {
        setRemainGauge(nTempRemainTime);
        timerStart();
    }

}

void MainGamePage::addLifeTime()
{
    // 정확한 선택에 의한 life gage 증가.
    qreal nTempRemainTime = getRemainingTime() + m_nAddLifeTimeInterval;
    qDebug() << Q_FUNC_INFO << getRemainingTime() << " " << m_nAddLifeTimeInterval;

    if (LIFE_MAX_TIME <= nTempRemainTime)
    {
        nTempRemainTime = LIFE_MAX_TIME;
    }

    setRemainGauge(nTempRemainTime);
    timerStart();
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
    timerStart();
}

void MainGamePage::onPauseButton()
{
    qDebug() << Q_FUNC_INFO;

    timerPaused();

    getComponent(OBJNAME_PAUSEPOPUP)->setVisible(true);
}

void MainGamePage::onClickedResumeButton()
{
    qDebug() << Q_FUNC_INFO;
    getComponent(OBJNAME_PAUSEPOPUP)->setVisible(false);
    startReadyCount(false);
}

void MainGamePage::onClickedSettingButton()
{
    qDebug() << Q_FUNC_INFO;
    HLauncherManager::instance()->pageTransition(HEnum::E_PAGE_SETTING);
}
