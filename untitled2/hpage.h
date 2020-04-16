#ifndef PAGE_H
#define PAGE_H

#include <QQuickItem>
#include <qquickwindow.h>

class HPage : public QQuickWindow
{
public:
    explicit HPage(QUrl urlSource);

protected:
    virtual void initialize();
    virtual void registerItem() {}

    QQuickItem *getComponent(const QString &strObjectName);

private:
    QQuickItem *m_qml;
    QUrl m_urlSource;
};

#endif // PAGE_H
