#include "bfswindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

BFSWindow::BFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Breadth-First Search");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createUnweightedGraph();
    renderer->runTraversalAnimation({
        "J","F","I","K","N","B","E","G","M","L","O","A","C","H","P","D"});

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
