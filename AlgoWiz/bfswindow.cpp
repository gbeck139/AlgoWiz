#include "bfswindow.h"
#include "graphalgorenderer.h"
#include <QLabel>

BFSWindow::BFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Breadth-First Search");
    resize(800, 800);

    QLabel *label = new QLabel("This is where we teach BFS!", this);
    label->move(50, 50);

    GraphAlgoRenderer* renderer = new GraphAlgoRenderer(this);

    renderer->createUnweightedGraph();

    renderer->runTraversalAnimation({"J", "F", "I", "K", "N", "B", "E", "G", "M", "L", "O", "A", "C", "H", "P", "D"});
}
