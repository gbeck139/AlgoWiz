#include "dijkstrawindow.h"
#include <QLabel>

DijkstraWindow::DijkstraWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Dijkstra's");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Dijkstra's!", this);
    label->move(50, 50);
}
