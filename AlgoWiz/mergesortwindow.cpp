#include "mergesortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "mergesortrenderer.h"

MergeSortWindow::MergeSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MergeSort");
    resize(600, 500);

    // Create a layout for the window
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the InsertionSortRenderer
    renderer = new mergeSortRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(renderer);

    // Set the layout
    setLayout(layout);
}
