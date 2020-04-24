#include "scoreboardpage.h"

#include "hlaunchermanager.h"
#include "hdatamanager.h"
#include <QJsonArray>
ScoreBoardPage::ScoreBoardPage() : HPage(QUrl("qrc:/ScoreBoardPage.qml"))
{
    initialize();
}

ScoreBoardPage::~ScoreBoardPage()
{

}

void ScoreBoardPage::initialize()
{
    connect(m_qml, SIGNAL(clickedRestartButton()), this, SLOT(onClickedRestartButton()));
    connect(m_qml, SIGNAL(clickedTitleButton()), this, SLOT(onClickedTitleButton()));

    m_qml->setProperty("rankModel", HDataManager::instance()->convertRankListToJsonArray());
}

void ScoreBoardPage::onClickedRestartButton()
{
    HLauncherManager::instance()->pageTransition(HEnum::E_PAGE_MAIN_GAME, HEnum::E_TRANSITION_SHOW_ALL_CLEAR);
}

void ScoreBoardPage::onClickedTitleButton()
{
    HLauncherManager::instance()->pageTransition(HEnum::E_PAGE_TITLE_PAGE, HEnum::E_TRANSITION_SHOW_ALL_CLEAR);
}
