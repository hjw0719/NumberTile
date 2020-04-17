#include "hlaunchermanager.h"
#include "hpage.h"

#include "HDefine.h"
#include <QQmlIncubator>
#include <qqmlcomponent.h>

HPage::HPage(QUrl urlSource) : m_qml(nullptr), m_urlSource(urlSource)
{
    auto engine = HLancherManager::instance()->getEngine();
    QQmlComponent *pComponent = new QQmlComponent(engine, m_urlSource);

    m_qml = qobject_cast<QQuickItem*>(pComponent->create());
    m_qml->setParentItem(this);
    qDebug() << m_qml;

#ifdef Q_OS_WIN
    m_qml->setProperty("width", DESKTOP_OS_WIDTH);
    m_qml->setProperty("height", DESKTOP_OS_HEIGHT);
#endif
}

void HPage::initialize()
{
    registerItem();
}


QQuickItem* HPage::getComponent(const QString &strObjectName)
{
    auto pItem = m_qml->findChild<QQuickItem*>(strObjectName);

    if (pItem)
    {
       return pItem;
    }
    else
    {
       return m_qml;
    }
}

void HPage::pageStop()
{
    this->setParentItem(nullptr);
    this->setParent(nullptr);
    this->setVisible(false);
}
