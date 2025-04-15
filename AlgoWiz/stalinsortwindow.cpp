#include "stalinsortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "stalinsortrenderer.h"

StalinSortWindow::StalinSortWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Stalinsort");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the title label
    QLabel *label = new QLabel("Stalin sort: It is always O(N) and works by 'taking out back' unsorted elements. "
                               "It is in place as well so it has constant memory (actually frees more up?!?). "
                               "This makes stalin sort one of the 'best' sorting algorithms if you are fine with "
                               "missing data at the end.",
                               this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);

    // Create the InsertionSortRenderer
    renderer = new StalinSortRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(renderer);

    // Set the layout
    setLayout(layout);
}
