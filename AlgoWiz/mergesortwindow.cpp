#include "mergesortwindow.h"
#include <QLabel>

MergeSortWindow::MergeSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MergeSort");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach MergeSort!", this);
    label->move(50, 50);
}
