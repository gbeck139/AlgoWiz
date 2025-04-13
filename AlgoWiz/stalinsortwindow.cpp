#include "stalinsortwindow.h"
#include <QLabel>

StalinSortWindow::StalinSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Stalinsort");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Communism!", this);
    label->move(50, 50);
}
