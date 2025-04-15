#ifndef STALINSORTWINDOW_H
#define STALINSORTWINDOW_H
#include <QWidget>
#include "stalinsortrenderer.h"

class StalinSortWindow : public QWidget
{
public:
    StalinSortWindow(QWidget *parent = nullptr);
    StalinSortRenderer* renderer;
};

#endif // STALINSORTWINDOW_H
