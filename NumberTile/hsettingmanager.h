#ifndef HSETTINGMANAGER_H
#define HSETTINGMANAGER_H

#include <QSharedPointer>
#include "HEnum.h"
#include <QObject>
#include <QMap>
#include <QSoundEffect>
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif
class HSettingManager : public QObject
{
        Q_OBJECT
public:
    HSettingManager(QObject *parent = NULL);
    ~HSettingManager();

    static HSettingManager *instance();
    void initialze();
    void initializeSound();
    void initializeFont();
    void initializeVibrate();

    static void doDelete(HSettingManager *manager);
    void setVolume(const HEnum::ESoundType eSoundType, const qreal fVolume);
    void setMute(const HEnum::ESoundType eSoundType, const bool bMute);

    qreal getVolume(const HEnum::ESoundType eSoundType);
    bool getMute(const HEnum::ESoundType eSoundType);

    void setPlaySoundStatus(const HEnum::ESoundType eSoundType, const bool bPlaying);

    void deviceVibrate(int nInterval);


private:
    QMap<HEnum::ESoundType, QSoundEffect*> m_tSoundSetting;
#ifdef Q_OS_ANDROID
    QAndroidJniObject vibrator;
#endif
};

#endif // HSETTINGMANAGER_H
