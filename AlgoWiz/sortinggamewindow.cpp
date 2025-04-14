#include "sortinggamewindow.h"
#include <QLabel>

SortingGameWindow::SortingGameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Sorting Game");
    resize(400, 300);

    QLabel *label = new QLabel("Sorting Game!", this);
    label->move(50, 50);
}

