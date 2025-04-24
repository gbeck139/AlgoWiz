#include "stalinsortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "stalinsortrenderer.h"

StalinSortWindow::StalinSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Stalinsort");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the InsertionSortRenderer
    renderer = new StalinSortRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(renderer);

    // Set the layout
    setLayout(layout);
}
