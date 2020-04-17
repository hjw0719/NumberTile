#include "hlaunchermanager.h"

#include "hpage.h"
#include "htile.h"
#include "maingamepage.h"
#include "HDefine.h"
#include "titlepage.h"
#include "scoreboardpage.h"

HLancherManager* HLancherManager::m_singleTonManager = NULL;

HLancherManager::HLancherManager()
{
}

HLancherManager::~HLancherManager()
{
    foreach (auto pPage, m_tPageList)
    {
        delete pPage;
        pPage = nullptr;
    }
}

void HLancherManager::initialize()
{
    m_engine = new QQmlApplicationEngine;

    m_pWindow = new QQuickWindow;
    registerItem();


#ifdef Q_OS_WIN
    m_pWindow->setWidth(DESKTOP_OS_WIDTH);
    m_pWindow->setHeight(DESKTOP_OS_HEIGHT);
#endif

    pageTransition(HEnum::E_PAGE_TITLE_PAGE);
    m_pWindow->show();
}

QQmlApplicationEngine *HLancherManager::getEngine()
{
    return m_engine;
}

HLancherManager *HLancherManager::instance()
{
    if (!m_singleTonManager)
    {
        m_singleTonManager = new HLancherManager();
    }

    return m_singleTonManager;
}

bool HLancherManager::pageTransition(const HEnum::EPageType ePageType, const HEnum::ETransitionType &eTransitionType)
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
        for (int i = m_tPageList.size() -1; i >= 0; i--)
        {
            auto pPage = m_tPageList.at(i);
            QString strTempPageObjectName = pPage->objectName();
            if (!strTempPageObjectName.compare(newPageObjectName))
            {
                pPage->setParentItem(m_pWindow->contentItem());
                pPage->setVisible(true);
                pPage->setEnabled(true);
            }
            else
            {
                deletePage(pPage);
                delete pPage;
            }
        }
    }   break;
    default : return false;
    }

    return true;
}

QString HLancherManager::enumToString(const HEnum::EPageType &ePageType)
{
    return QVariant::fromValue(ePageType).toString();
}

void HLancherManager::createPage(const HEnum::EPageType ePageType)
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

void HLancherManager::deletePage(HPage *pDeletePage)
{
    if (pDeletePage)
    {
        pDeletePage->pageStop();
    }
    delete pDeletePage;
}

HPage *HLancherManager::getCurrentPage()
{
    if (m_tPageList.size())
    {
        return m_tPageList.last();
    }
    return nullptr;
}

void HLancherManager::pageClose()
{
    if (2 > m_tPageList.size())
    {
        return;
    }

    auto currentPage = m_tPageList.takeLast();
    deletePage(currentPage);

    auto beforePage = m_tPageList.last();
    beforePage->setParentItem(m_pWindow->contentItem());
    beforePage->setVisible(true);
    beforePage->setEnabled(true);
}

void HLancherManager::registerItem()
{
    qmlRegisterType<HTile>("HTile", 1, 0, "HTile");
    qmlRegisterType<HEnum>("HEnum", 1, 0, "HEnum");
}
