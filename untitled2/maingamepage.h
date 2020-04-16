#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include "hpage.h"
#include <QTimer>
class MainGamePage : public HPage
{
    Q_OBJECT
public:
    MainGamePage();
    ~MainGamePage();
    virtual void initialize() override;
    void reduceAddtimeInterval();

protected:
    void setRemainGauge(int nRemainGauge);
protected slots:
    void reduceLifeTime();
    void addLifeTime();

private:
    QTimer m_LifeTimer;
    int m_nAddLifeTimeInterval;

};

#endif // MAINGAMEPAGE_H
