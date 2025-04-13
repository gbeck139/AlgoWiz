#include "runtimewindow.h"
#include <QLabel>

RuntimeWindow::RuntimeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Runtime");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach Runtime!", this);
    label->move(50, 50);
}
