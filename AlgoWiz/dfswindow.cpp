#include "dfswindow.h"
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach DFS!", this);
    label->move(50, 50);
}
