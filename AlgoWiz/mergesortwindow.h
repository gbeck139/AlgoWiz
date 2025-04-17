#ifndef MERGESORTWINDOW_H
#define MERGESORTWINDOW_H

#include <QWidget>
#include "mergesortrenderer.h"

class MergeSortWindow : public QWidget
{
public:
    MergeSortWindow(QWidget *parent = nullptr);

private:
    mergeSortRenderer *renderer;
};

#endif // MERGESORTWINDOW_H
