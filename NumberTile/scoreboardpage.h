#ifndef SCOREBOARDPAGE_H
#define SCOREBOARDPAGE_H

#include "hpage.h"

class ScoreBoardPage : public HPage
{
    Q_OBJECT
public:
    explicit ScoreBoardPage();
    virtual ~ScoreBoardPage();

protected:
    void initialize() override;

protected slots :

    void onClickedRestartButton();
    void onClickedTitleButton();

};

#endif // SCOREBOARDPAGE_H
