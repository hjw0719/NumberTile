#include "hsettingpage.h"
#include "hsettingmanager.h"
#include "hlaunchermanager.h"

#define OBJNAME_BGMSLIDER "id_bgmSlider"
#define OBJNAME_EFFECTSLIDER  "id_effectSlider"
#define OBJNAME_BACKBUTTON "id_backButton"
#define OBJNAME_BGMMUTEBUTTON "id_BGMMuteButton"
#define OBJNAME_EFFECTMUTEBUTTON "id_effectMuteButton"

HSettingPage::HSettingPage() :
    HPage(QUrl("qrc:/SettingPage.qml"))
{
    initialize();
}

void HSettingPage::initialize()
{
    HPage::initialize();

    connect(getComponent(OBJNAME_BGMSLIDER), SIGNAL(soundValueChanged(int)), this, SLOT(onBGMSoundValueChanged(int)));
    connect(getComponent(OBJNAME_EFFECTSLIDER), SIGNAL(soundValueChanged(int)), this, SLOT(onEffectSoundValueChanged(int)));
    connect(getComponent(OBJNAME_BACKBUTTON), SIGNAL(backButtonClicked()), this, SLOT(onBackButtonClicked()));
    connect(getComponent(OBJNAME_BGMMUTEBUTTON), SIGNAL(soundMuteChanged(bool)), this, SLOT(onBGMMuteChanged(bool)));
    connect(getComponent(OBJNAME_EFFECTMUTEBUTTON), SIGNAL(soundMuteChanged(bool)), this, SLOT(onEffectMuteChanged(bool)));

    int nBGMVolume = HSettingManager::instance()->getVolume(HEnum::E_SOUND_BGM) * 100;
    int nEffectVolume = HSettingManager::instance()->getVolume(HEnum::E_SOUND_BUTTON_TOUCH) * 100;

    getComponent(OBJNAME_BGMSLIDER)->setProperty("value", nBGMVolume);
    getComponent(OBJNAME_EFFECTSLIDER)->setProperty("value", nEffectVolume);
}

void HSettingPage::onBGMSoundValueChanged(int nValue)
{
    qreal realVolume = nValue / 100.0;

    HSettingManager::instance()->setVolume(HEnum::E_SOUND_BGM, realVolume);
    HSettingManager::instance()->setVolume(HEnum::E_SOUND_FEVER_BGM, realVolume);
}

void HSettingPage::onEffectSoundValueChanged(int nValue)
{
    qreal realVolume = nValue / 100.0;

    HSettingManager::instance()->setVolume(HEnum::E_SOUND_BUTTON_TOUCH, realVolume);
    HSettingManager::instance()->setVolume(HEnum::E_SOUND_TILE_SUCCESS, realVolume);
    HSettingManager::instance()->setVolume(HEnum::E_SOUND_TILE_FAIL, realVolume);
    HSettingManager::instance()->setVolume(HEnum::E_SOUND_FEVER_TOUCH, realVolume);
}

void HSettingPage::onBackButtonClicked()
{
    HLauncherManager::instance()->pageClose();
}

void HSettingPage::onBGMMuteChanged(bool bMute)
{
    HSettingManager::instance()->setMute(HEnum::E_SOUND_BGM, bMute);
    HSettingManager::instance()->setMute(HEnum::E_SOUND_FEVER_BGM, bMute);
}

void HSettingPage::onEffectMuteChanged(bool bMute)
{
    HSettingManager::instance()->setMute(HEnum::E_SOUND_BUTTON_TOUCH, bMute);
    HSettingManager::instance()->setMute(HEnum::E_SOUND_TILE_SUCCESS, bMute);
    HSettingManager::instance()->setMute(HEnum::E_SOUND_TILE_FAIL, bMute);
    HSettingManager::instance()->setMute(HEnum::E_SOUND_FEVER_TOUCH, bMute);
}
