#include "selectionsortwindow.h"
#include <QLabel>

SelectionSortWindow::SelectionSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Selectionsort");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Selectionsort!", this);
    label->move(50, 50);
}
