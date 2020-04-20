#include "hlaunchermanager.h"
#include "HEnum.h"
#include "titlepage.h"

#define OBJNAME_MOUSEAREA "id_mouseArea"

TitlePage::TitlePage() :
    HPage(QUrl("qrc:/TitlePage.qml"))
{
    initialize();
}

TitlePage::~TitlePage()
{

}

void TitlePage::initialize()
{
    HPage::initialize();

    bool bSuccess = connect(getComponent(OBJNAME_MOUSEAREA), SIGNAL(clickedPage()), this, SLOT(onClickedPage()));
    qDebug() <<Q_FUNC_INFO << bSuccess;
}

void TitlePage::onClickedPage()
{
    qDebug() << Q_FUNC_INFO;
    HLauncherManager::instance()->pageTransition(HEnum::E_PAGE_MAIN_GAME, HEnum::E_TRANSITION_SHOW_ALL_CLEAR);
}
