#ifndef PAGE_H
#define PAGE_H

#include <QQuickItem>
#include <qquickwindow.h>

class HPage : public QQuickItem
{
    Q_OBJECT
public:
    explicit HPage(QUrl urlSource);

protected:
    virtual void initialize();
    virtual void registerItem() {}

    QQuickItem *getComponent(const QString &strObjectName);

protected:
    QQuickItem *m_qml;

private:
    QUrl m_urlSource;
};

#endif // PAGE_H
