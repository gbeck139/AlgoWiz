#include "graphtheorywindow.h"
#include <QLabel>


GraphTheoryWindow::GraphTheoryWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Graph Theory");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Graph Theory!", this);
    label->move(50, 50);
}
