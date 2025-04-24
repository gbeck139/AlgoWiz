#include "binarysearchwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "binarysearchrenderer.h"

BinarySearchWindow::BinarySearchWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("BinarySearch");
    resize(600, 500);

    // Create a layout for the window
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the BinarySearchRenderer
    renderer = new BinarySearchRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(renderer);

    // Set the layout
    setLayout(layout);
}

