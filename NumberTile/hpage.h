#ifndef PAGE_H
#define PAGE_H

#include <QQuickItem>

class HPage : public QQuickItem
{
    friend class HLauncherManager;
    Q_OBJECT
public:
    explicit HPage(QUrl urlSource);

protected:
    virtual void initialize();
    virtual void registerItem() {}

    QQuickItem *getComponent(const QString &strObjectName);
    void pageStop();

protected:
    QQuickItem *m_qml;

private:
    QUrl m_urlSource;

};

#endif // PAGE_H
