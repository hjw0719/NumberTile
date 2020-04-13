#include "manager.h"
#include "page.h"
#include "util.h"
#include <QQmlIncubator>
#include <qqmlcomponent.h>

Page::Page(QUrl urlSource) : m_qml(nullptr), m_urlSource(urlSource)
{
    auto engine = Manager::instance()->getEngine();
    QQmlComponent *pComponent = new QQmlComponent(engine, m_urlSource);

    m_qml = qobject_cast<QQuickItem*>(pComponent->create());
    m_qml->setParentItem(this->contentItem());
    qDebug() << m_qml;

    this->setWidth(PAGE_SIZE_WIDTH);
    this->setHeight(PAGE_SIZE_HEIGHT);

    m_qml->setWidth(PAGE_SIZE_WIDTH);
    m_qml->setHeight(PAGE_SIZE_HEIGHT);
}

QQuickItem* Page::getComponent(const QString &strObjectName)
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
