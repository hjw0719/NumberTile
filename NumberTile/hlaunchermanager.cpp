#include "hlaunchermanager.h"

#include "hpage.h"
#include "htile.h"
#include "hgamer.h"
#include "maingamepage.h"
#include "HDefine.h"
#include "titlepage.h"
#include "scoreboardpage.h"
#include "hsettingmanager.h"
#include "hsettingpage.h"
#include "hwindow.h"

HLauncherManager* HLauncherManager::m_singleTonManager = NULL;

HLauncherManager::HLauncherManager()
{
}

HLauncherManager::~HLauncherManager()
{
    foreach (auto pPage, m_tPageList)
    {
        delete pPage;
        pPage = nullptr;
    }
}

void HLauncherManager::initialize()
{
    m_engine = new QQmlApplicationEngine;

    m_pWindow = new HWindow;
    registerItem();
    HSettingManager::instance()->initialze();

#ifdef Q_OS_WIN
    m_pWindow->setWidth(DESKTOP_OS_WIDTH);
    m_pWindow->setHeight(DESKTOP_OS_HEIGHT);
#endif

    pageTransition(HEnum::E_PAGE_TITLE_PAGE);
    m_pWindow->show();
}

QQmlApplicationEngine *HLauncherManager::getEngine()
{
    return m_engine;
}

HLauncherManager *HLauncherManager::instance()
{
    if (!m_singleTonManager)
    {
        m_singleTonManager = new HLauncherManager();
    }

    return m_singleTonManager;
}

bool HLauncherManager::pageTransition(const HEnum::EPageType ePageType, const HEnum::ETransitionType &eTransitionType)
{
    QString newPageObjectName = enumToString(ePageType);

    auto pCurrentPage = getCurrentPage();

    if(pCurrentPage)
    {
        QString strCurrentPageObjectName = enumToString(ePageType);
        if (strCurrentPageObjectName.compare(newPageObjectName))
        {
            return false;
        }

        pCurrentPage->pageStop();
    }

    switch (eTransitionType)
    {
    case HEnum::E_TRANSITION_SHOW_ALL_CLEAR:
    {
        foreach(auto pPage, m_tPageList)
        {
            deletePage(pPage);
        }

        m_tPageList.clear();
        createPage(ePageType);
    }   break;

    case HEnum::E_TRANSITION_SHOW_APPEND:
    {
        createPage(ePageType);
    }   break;

    case HEnum::E_TRANSITION_SHOW_RETURN:
    {
        while (m_tPageList.size())
        {
            auto pPage = m_tPageList.takeLast();
            if (!pPage)
            {
                return false;
            }

            QString strTempPageObjectName = pPage->objectName();
            if (!strTempPageObjectName.compare(newPageObjectName))
            {
                pPage->setParentItem(m_pWindow->contentItem());
                pPage->setVisible(true);
                pPage->setEnabled(true);
                m_tPageList.append(pPage);
                return true;
            }
            else
            {
                deletePage(pPage);
            }
        }
    }   break;
    default : return false;
    }

    return true;
}

QString HLauncherManager::enumToString(const HEnum::EPageType &ePageType)
{
    return QVariant::fromValue(ePageType).toString();
}

void HLauncherManager::createPage(const HEnum::EPageType ePageType)
{
    HPage* pNewPage = Q_NULLPTR;
    switch (ePageType)
    {
    case HEnum::E_PAGE_TITLE_PAGE:
    {
        pNewPage = new TitlePage;
    }   break;
    case HEnum::E_PAGE_MAIN_GAME:
    {
        pNewPage = new MainGamePage;
    }   break;
    case HEnum::E_PAGE_SCORE_BOARD:
    {
        pNewPage = new ScoreBoardPage;
    }   break;
    case HEnum::E_PAGE_SETTING:
    {
        pNewPage = new HSettingPage;
    }   break;
    default : return;
    }

    if (pNewPage)
    {
        pNewPage->setObjectName(enumToString(ePageType));
        pNewPage->setVisible(true);
        pNewPage->setParentItem(m_pWindow->contentItem());
        m_tPageList.append(pNewPage);
    }
}

void HLauncherManager::deletePage(HPage *pDeletePage)
{
    if (pDeletePage)
    {
        pDeletePage->pageStop();
    }
    delete pDeletePage;
}

HPage *HLauncherManager::getCurrentPage()
{
    if (m_tPageList.size())
    {
        return m_tPageList.last();
    }
    return nullptr;
}

void HLauncherManager::pageClose()
{
    qDebug() << Q_FUNC_INFO << "Page size : " << m_tPageList.size();
    if (2 > m_tPageList.size())
    {
        qApp->quit();
        return;
    }

    auto currentPage = m_tPageList.takeLast();
    deletePage(currentPage);

    auto beforePage = m_tPageList.last();
    beforePage->setVisible(true);
    beforePage->setEnabled(true);
}

void HLauncherManager::registerItem()
{
    qmlRegisterType<HTile>("HTile", 1, 0, "HTile");
    qmlRegisterType<HEnum>("HEnum", 1, 0, "HEnum");
}
