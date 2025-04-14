#include "binarysearchwindow.h"
#include <QLabel>

BinarySearchWindow::BinarySearchWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Binary Search");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Binary Search!", this);
    label->move(50, 50);
}

