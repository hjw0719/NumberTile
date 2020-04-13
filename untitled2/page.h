#ifndef PAGE_H
#define PAGE_H

#include <QQuickItem>
#include <qquickwindow.h>

class Page : public QQuickWindow
{
public:
    Page(QUrl urlSource);

protected:
    QQuickItem *getComponent(const QString &strObjectName);

private:
    QQuickItem *m_qml;
    QUrl m_urlSource;
};

#endif // PAGE_H
