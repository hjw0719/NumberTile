#ifndef TITLEPAGE_H
#define TITLEPAGE_H

#include "hpage.h"

class TitlePage : public HPage
{
    Q_OBJECT
public:
    explicit TitlePage();
    virtual ~TitlePage();

protected:
    void initialize() override;

protected slots:
    void onClickedPage();
    void onClickedSettingButton();
};

#endif // TITLEPAGE_H
