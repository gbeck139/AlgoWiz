#include "dfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();
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

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
