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
    void timerStart(const int &nTime);
    void startReadyCount();

protected slots :
    void onLifeTimeEnd();
    void onUpdateUI(HEnum::EUpdateUIType eUpdateUIType);
    void reduceLifeTime();
    void addLifeTime();
    void onClickedRestartButton();
    void onClickedScoreBoardButton();
    void onReadyCountOver();

private:
    QTimer *m_pLifeTimer;
    int m_nAddLifeTimeInterval;

};

#endif // MAINGAMEPAGE_H
