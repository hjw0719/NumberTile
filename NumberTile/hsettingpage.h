#ifndef HSETTINGPAGE_H
#define HSETTINGPAGE_H

#include "hpage.h"

class HSettingPage : public HPage
{
    Q_OBJECT
public:
    explicit HSettingPage();

protected:
    virtual void initialize() override;

protected slots :
    void onBGMSoundValueChanged(int nValue);
    void onEffectSoundValueChanged(int nValue);
    void onBackButtonClicked();
    void onBGMMuteChanged(bool bMute);
    void onEffectMuteChanged(bool bMute);
};

#endif // HSETTINGPAGE_H
