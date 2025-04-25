/**
 * @file dfswindow.cpp
 * @author Jared Pratt, Grant Beck
 * @brief Implementation of the DFSWindow class, which sets up the DFS algorithm visualization window.
 * @date 2025-04-25
 */

#include "dfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");

    // Create the graph renderer and generate the unweighted graph
    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();

    // Run the DFS traversal animation with a predefined traversal order
    renderer->runTraversalAnimation({
        "J", "_16",
        "F", "_15",
        "B", "_0",
        "A", "_12",
        "E", "_13",
        "I", "_14",
        "M", "_9",
        "N", "_10",
        "O", "_20",
        "K", "_19",
        "G", "_18",
        "C", "_2",
        "D", "_21",
        "H", "_22",
        "L", "_23",
        "P"
    });

    // Set up layout and add the renderer widget
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
