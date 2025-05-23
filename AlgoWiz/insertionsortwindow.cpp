/**
 * @file insertionsortwindow.cpp
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the implementation of the insertion sort window class.
 * @date 2025-04-24
 */

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
    

    // Create the InsertionSortRenderer
    renderer = new InsertionSortRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(renderer);
    

    // Set the layout
    setLayout(layout);
}
