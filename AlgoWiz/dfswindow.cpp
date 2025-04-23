#include "dfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();
    renderer->runTraversalAnimation({
        "J","F","B","A","E","I","M","N", "O","K","G","C","D","H","L","P"});

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
