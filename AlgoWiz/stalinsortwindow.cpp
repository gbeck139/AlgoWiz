/**
 * @file stalinsortwindow.cpp
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the implementation of the Stalin sort window class.
 * @date 2025-04-24
 */

#include "stalinsortwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "stalinsortrenderer.h"

/**
 * @brief StalinSortWindow constructor
 * @param parent The parent widget
 */
StalinSortWindow::StalinSortWindow(QWidget *parent) : QWidget(parent)
{
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
