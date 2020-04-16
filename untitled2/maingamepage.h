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
    void setScoreText(const qulonglong &nScore);
    void setComboText(const quint16 &nCombo);

protected slots :
    void onUpdateUI(HEnum::ETouchStatus eTouchStatus);
    void reduceLifeTime();
    void addLifeTime();

private:
    QTimer m_LifeTimer;
    int m_nAddLifeTimeInterval;

};

#endif // MAINGAMEPAGE_H
