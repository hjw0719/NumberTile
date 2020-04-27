#include "hsettingmanager.h"
#include <QSound>

#include <HDefine.h>
#include <QGuiApplication>
#include <QDebug>
#include <QFile>
#include <QFont>
#include <QFontDatabase>

QSharedPointer<HSettingManager> settingObj = NULL;

HSettingManager::HSettingManager(QObject *parent) :
        QObject(parent)
{

}

HSettingManager::~HSettingManager()
{

}

HSettingManager *HSettingManager::instance()
{
    if (settingObj.isNull())
    {
        settingObj = QSharedPointer<HSettingManager>(new HSettingManager, &HSettingManager::doDelete);
    }

    return settingObj.data();
}

void HSettingManager::initialze()
{
    initializeSound();
    initializeFont();


}

void HSettingManager::initializeSound()
{
    for (int i = 0; i < HEnum::E_SOUND_MAX; i++)
    {
        QSoundEffect *pTempSoundEffect = new QSoundEffect;
        m_tSoundSetting.insert((HEnum::ESoundType)i, pTempSoundEffect);
        pTempSoundEffect->setMuted(false);
        pTempSoundEffect->setVolume(SOUND_VOUME_DEFAULT);
        pTempSoundEffect->setLoopCount(0);

        switch (i)
        {
        case HEnum::E_SOUND_BGM:
        {
            pTempSoundEffect->setLoopCount(QSoundEffect::Infinite);
            pTempSoundEffect->setSource(QUrl(""));
        }   break;
        case HEnum::E_SOUND_FEVER_BGM:
        {
            pTempSoundEffect->setLoopCount(QSoundEffect::Infinite);
            pTempSoundEffect->setSource(QUrl(""));
        }   break;
        case HEnum::E_SOUND_FEVER_TOUCH:
        {
            pTempSoundEffect->setSource(QUrl(""));
        }   break;
        case HEnum::E_SOUND_TILE_SUCCESS:
        {
            pTempSoundEffect->setSource(QUrl(SOUND_URL_TILE_TOUCH_SUCCESS));
        }   break;
        case HEnum::E_SOUND_TILE_FAIL:
        {
            pTempSoundEffect->setSource(QUrl(SOUND_URL_TILE_TOUCH_FAIL));
        }   break;
        case HEnum::E_SOUND_BUTTON_TOUCH:
        {
            pTempSoundEffect->setSource(QUrl(""));
        }   break;
        default: continue;
        }
    }
}

void HSettingManager::initializeFont()
{
    QString appFolderPath = QGuiApplication::applicationDirPath();
    qDebug() << "App Folder : " << appFolderPath;


    QStringList fontFiles;
    QStringList normalFontFamily;
    QStringList boldFontFamily;

    //================================================================================================================
    normalFontFamily << "NanumGothicCoding";
    boldFontFamily << "NanumGothicCoding-Bold";

    fontFiles << QString("%1%2%3").arg(appFolderPath).arg(FONT_PATH).arg("NanumGothicCoding.ttf");
    fontFiles << QString("%1%2%3").arg(appFolderPath).arg(FONT_PATH).arg("NanumGothicCoding-Bold.ttf");

    //================================================================================================================

    foreach (const QString &strFontPath, fontFiles)
    {
        qDebug() << "Font files : " << strFontPath;

        QFile fontFile(strFontPath);
        if(false == fontFile.open(QIODevice::ReadOnly))
        {
            continue;
        }

        QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        fontFile.close();
    }

    QFont font("NanumGothicCoding");

    QGuiApplication::setFont(font);
}

void HSettingManager::doDelete(HSettingManager *manager)
{
    if (nullptr != manager)
    {
        delete manager;
    }
}

void HSettingManager::setVolume(const HEnum::ESoundType eSoundType, const qreal fVolume)
{
    setMute(eSoundType, false);
    auto tSoundEffect = m_tSoundSetting.value(eSoundType);
    if (tSoundEffect)
    {
        tSoundEffect->setVolume(fVolume);
    }
}

void HSettingManager::setMute(const HEnum::ESoundType eSoundType, const bool bMute)
{
    auto tSoundEffect = m_tSoundSetting.value(eSoundType);
    if (tSoundEffect)
    {
        setPlaySoundStatus(eSoundType, !bMute);
        tSoundEffect->setMuted(bMute);
    }
}

qreal HSettingManager::getVolume(const HEnum::ESoundType eSoundType)
{
    auto tSoundEffect = m_tSoundSetting.value(eSoundType);
    if (tSoundEffect)
    {
        return tSoundEffect->volume();
    }
    else
    {
        return -1;
    }
}

bool HSettingManager::getMute(const HEnum::ESoundType eSoundType)
{
    auto tSoundEffect = m_tSoundSetting.value(eSoundType);
    if (tSoundEffect)
    {
        return tSoundEffect->isMuted();
    }
    else
    {
        return false;
    }
}

void HSettingManager::setPlaySoundStatus(const HEnum::ESoundType eSoundType, const bool bPlaying)
{
    auto tSoundEffect = m_tSoundSetting.value(eSoundType);
    if (tSoundEffect)
    {
        if (bPlaying)
        {
            tSoundEffect->play();
        }
        else
        {
            tSoundEffect->stop();
        }
    }
}
