/**
 * @file graphtheorywindow.cpp
 * @brief Implementation of the GraphTheoryWindow class, which sets up the graph theory visualization window.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#include "graphtheorywindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

GraphTheoryWindow::GraphTheoryWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Graph Theory");

    // Create the graph renderer and generate the theory graph
    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createTheoryGraph();

    // Set up the layout and add the renderer widget
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
