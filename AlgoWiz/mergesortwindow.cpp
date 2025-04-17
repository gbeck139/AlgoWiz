#include "mergesortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "mergesortrenderer.h"

MergeSortWindow::MergeSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("MergeSort");
    resize(600, 500);

    // Create a layout for the window
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the title label
    QLabel *label = new QLabel(
        "Merge sort is an O(NLogN) in all cases sorting algorithm that is O(N) in space "
        "complexity. It starts by splitting a list into elements of size 1, and then merging each "
        "of those lists back together, swapping the ordering along the way as needed. This "
        "visualization shows the \"second half\" of the sort, and sorts the left subtrees first.",
        this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);

    // Create the InsertionSortRenderer
    renderer = new mergeSortRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(renderer);

    // Set the layout
    setLayout(layout);
}
