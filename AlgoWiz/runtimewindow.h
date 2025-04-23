#ifndef RUNTIMEWINDOW_H
#define RUNTIMEWINDOW_H

#include <QWidget>

class RuntimeWindow : public QWidget
{
public:
    RuntimeWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *evt);
};

#endif // RUNTIMEWINDOW_H
