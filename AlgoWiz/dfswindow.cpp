#include "dfswindow.h"
#include "graphalgorenderer.h"
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");
    resize(800, 800);

    QLabel *label = new QLabel("This is where we teach DFS!", this);
    label->move(50, 50);

    GraphAlgoRenderer* renderer = new GraphAlgoRenderer(this);

    renderer->createUnweightedGraph();

    renderer->runTraversalAnimation({"J", "F", "B", "A", "E", "I", "M", "N", "O", "K", "G", "C", "D", "H", "L", "P"});
}


