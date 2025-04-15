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
    QLabel *label = new QLabel("Insertion sort: in the best case, it's O(n), in the average "
                               "and worst case, it's O(n^2). It accomplishes"
                               "its best case with a conditional inner while-loop that checks if, "
                               "in this case, the bar is already in its correct position."
                               "It grows a \"sorted\" portion at each outer loop iteration, and "
                               "then moves the rightmost bar to its proper place.",
                               this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);

    // QLabel *label = new QLabel("This is where we teach MergeSort!", this);
    // label->move(50, 50);

    // Create the InsertionSortRenderer
    renderer = new InsertionSortRenderer();
    renderer->setMinimumHeight(300);
    
    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(renderer);
    
    // Set the layout
    setLayout(layout);
}
