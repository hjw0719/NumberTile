#include "hlaunchermanager.h"
#include "hwindow.h"

HWindow::HWindow(QWindow *parent) :
    QQuickWindow(parent)
{

}

bool HWindow::event(QEvent *event)
{
    QKeyEvent *pKeyEvent = dynamic_cast<QKeyEvent *>(event);
    if (pKeyEvent)
    {
        if (pKeyEvent->type() == QEvent::KeyRelease)
        {
            if (pKeyEvent->key() == Qt::Key_Back)
            {
                HLauncherManager::instance()->pageClose();
            }
        }
        return true;
    }

    return QQuickWindow::event(event);
}
