/**
 * @file bfswindow.cpp
 * @author Jared Pratt, Grant Beck
 * @brief Implementation of the BFSWindow class, which sets up the BFS algorithm visualization window.
 * @date 2025-04-25
 */

#include "bfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

BFSWindow::BFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Breadth-First Search");

    // Create the graph renderer and generate the unweighted graph
    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();

    // Run the BFS traversal animation with a predefined traversal order
    renderer->runTraversalAnimation({
        "J", "_16", "_6", "_17", "_7",
        "F", "_15", "_3", "_4",
        "I", "_14",
        "N", "_10",
        "K", "_8",
        "B", "_0", "_1",
        "E",
        "G", "_5",
        "M",
        "O", "_11",
        "L",
        "A",
        "C", "_2",
        "P",
        "H",
        "D"
    });

    // Set up layout and add the renderer widget
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
