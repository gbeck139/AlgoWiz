#include "insertionsortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "insertionsortrenderer.h"

InsertionSortWindow::InsertionSortWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Insertionsort");
    resize(600, 500);

    // Create a layout for the window
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Create the title label
    QLabel *label = new QLabel("Insertion Sort Visualization", this);
    label->setAlignment(Qt::AlignCenter);
    
    // Create the InsertionSortRenderer
    renderer = new InsertionSortRenderer();
    renderer->setMinimumHeight(300);
    
    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(renderer);
    
    // Set the layout
    setLayout(layout);
}
