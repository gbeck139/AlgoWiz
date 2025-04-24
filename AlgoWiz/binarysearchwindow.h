#ifndef BINARYSEARCHWINDOW_H
#define BINARYSEARCHWINDOW_H

#include <QWidget>
//#include <QPushButton>
#include "binarysearchrenderer.h"
//#include "quizwindow.h"

class BinarySearchWindow : public QWidget
{
public:
    BinarySearchWindow(QWidget *parent = nullptr);

private:
    BinarySearchRenderer *renderer;
};

#endif // BINARYSEARCHWINDOW_H
