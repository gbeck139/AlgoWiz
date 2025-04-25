#include "bfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

BFSWindow::BFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Breadth-First Search");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();
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

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
