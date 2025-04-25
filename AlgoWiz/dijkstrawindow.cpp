/**
 * @file dijkstrawindow.cpp
 * @brief Implementation of the DijkstraWindow class, which sets up the Dijkstra's algorithm visualization window.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 *
 */
#include "dijkstrawindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

DijkstraWindow::DijkstraWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Dijkstra’s Algorithm");

    // Create the graph renderer and generate the weighted graph
    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createWeightedGraph();

    // Run the Dijkstra traversal animation with a predefined traversal order
    renderer->runTraversalAnimation({
        "A","_0",".B.2","_1",".D.8",
        "B","_2",".D.7","_3",".E.8",
        "D","_5",".F.9","_4",
        "E","_6","_8",".C.17",
        "F","_7","C"});

    // Set up layout and add the renderer widget
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
