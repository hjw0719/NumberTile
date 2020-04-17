#include "hwindow.h"

HWindow::HWindow() : QQuickWindow()
{

}

bool HWindow::event(QEvent *event)
{
    return true;
}
