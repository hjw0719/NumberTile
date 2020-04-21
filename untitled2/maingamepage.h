#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include "hpage.h"
#include <QTimer>
#include "HEnum.h"

class MainGamePage : public HPage
{
    Q_OBJECT
public:
    explicit MainGamePage();
    virtual ~MainGamePage();
    virtual void initialize() override;
    void reduceAddtimeInterval();

protected:
    void setRemainGauge(int nRemainGauge);
    void setScoreText(const uint64_t &nScore);
    void setComboText(const uint16_t &nCombo);
    void setFeverMode(const bool &bFever);
    void gameOver();
    void gameStart();
    void timerStart();
    void timerPaused();
    void timerStop();
    qreal getRemainingTime();
    bool getisTimerRunning();
    void startReadyCount(bool bInit = true);

protected slots :
    void onLifeTimeEnd();
    void onUpdateUI(HEnum::EUpdateUIType eUpdateUIType);
    void reduceLifeTime();
    void addLifeTime();
    void onClickedRestartButton();
    void onClickedScoreBoardButton();
    void onReadyCountOver();
    void onResumedButton();

private:
    int m_nAddLifeTimeInterval;

};

#endif // MAINGAMEPAGE_H
