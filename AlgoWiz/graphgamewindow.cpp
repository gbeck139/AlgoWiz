#include "graphgamewindow.h"
#include <QLabel>

GraphGameWindow::GraphGameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Graph Game");
    resize(400, 300);

    QLabel *label = new QLabel("Graph Game!", this);
    label->move(50, 50);
}

