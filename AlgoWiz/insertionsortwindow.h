#ifndef INSERTIONSORTWINDOW_H
#define INSERTIONSORTWINDOW_H

#include <QWidget>
#include "insertionsortrenderer.h"

class InsertionSortWindow : public QWidget
{
public:
    InsertionSortWindow(QWidget *parent = nullptr);

private:
    InsertionSortRenderer *renderer;
};

#endif // INSERTIONSORTWINDOW_H
