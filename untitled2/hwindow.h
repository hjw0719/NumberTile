#ifndef HWINDOW_H
#define HWINDOW_H

#include <qquickwindow.h>



class HWindow : public QQuickWindow
{
public:
    HWindow();

    // QObject interface
    public:
        bool event(QEvent *event);
};

#endif // HWINDOW_H
