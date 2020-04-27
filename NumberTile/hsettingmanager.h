#ifndef HSETTINGMANAGER_H
#define HSETTINGMANAGER_H

#include <QSharedPointer>
#include "HEnum.h"
#include <QObject>
#include <QMap>
#include <QSoundEffect>
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

    static void doDelete(HSettingManager *manager);
    void setVolume(const HEnum::ESoundType eSoundType, const qreal fVolume);
    void setMute(const HEnum::ESoundType eSoundType, const bool bMute);

    qreal getVolume(const HEnum::ESoundType eSoundType);
    bool getMute(const HEnum::ESoundType eSoundType);

    void setPlaySoundStatus(const HEnum::ESoundType eSoundType, const bool bPlaying);

private:
    QMap<HEnum::ESoundType, QSoundEffect*> m_tSoundSetting;
};

#endif // HSETTINGMANAGER_H
