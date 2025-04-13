#include "bfswindow.h"
#include <QLabel>

BFSWindow::BFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Best-First Search");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach BFS!", this);
    label->move(50, 50);
}
