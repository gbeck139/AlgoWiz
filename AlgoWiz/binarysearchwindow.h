#ifndef BINARYSEARCHWINDOW_H
#define BINARYSEARCHWINDOW_H

#include <QWidget>
#include "binarysearchrenderer.h"

class BinarySearchWindow : public QWidget
{
public:
    BinarySearchWindow(QWidget *parent = nullptr);

private:
    BinarySearchRenderer *renderer;
};

#endif // BINARYSEARCHWINDOW_H
