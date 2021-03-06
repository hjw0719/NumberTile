#ifndef MANAGE_H
#define MANAGE_H

#include <QQmlApplicationEngine>
#include <HEnum.h>

// 화면전환 및 화면 설정과 관련된 구현부.
class HWindow;
class HPage;
class HLauncherManager
{
private:
    explicit HLauncherManager();
    ~HLauncherManager();

public:
    void initialize();
    QQmlApplicationEngine *getEngine();
    static HLauncherManager *instance();

    //화면 전환 관련 함수.
    bool pageTransition(const HEnum::EPageType ePageType, const HEnum::ETransitionType &eTransitionType = HEnum::E_TRANSITION_SHOW_APPEND);
    QString enumToString(const HEnum::EPageType &ePageType);
    void createPage(const HEnum::EPageType ePageType);
    void deletePage(HPage* pDeletePage);
    HPage* getCurrentPage();
    void pageClose();

protected:
    void registerItem();

private:
    QQmlApplicationEngine *m_engine;
    static HLauncherManager* m_singleTonManager;
    HWindow *m_pWindow;
    QList<HPage *> m_tPageList;

};

#endif // MANAGE_H
