#ifndef HWINDOW_H
#define HWINDOW_H

#include <qquickwindow.h>



class HWindow : public QQuickWindow
{
public:
    explicit HWindow(QWindow *parent = nullptr);

    // QObject interface
    public:
        bool event(QEvent *event) override;
};

#endif // HWINDOW_H
