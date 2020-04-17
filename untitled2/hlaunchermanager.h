#ifndef MANAGE_H
#define MANAGE_H

#include <QQmlApplicationEngine>
#include <qquickwindow.h>
#include <HEnum.h>

// 화면전환 및 화면 설정과 관련된 구현부.
class HPage;
class HLancherManager
{
private:
    explicit HLancherManager();
    ~HLancherManager();

public:
    void initialize();
    QQmlApplicationEngine *getEngine();
    static HLancherManager *instance();

    //화면 전환 관련 함수.
    void closePage();
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
    static HLancherManager* m_singleTonManager;
    QQuickWindow *m_pWindow;
    QList<HPage *> m_tPageList;

};

#endif // MANAGE_H
