#include "dfswindow.h"
#include "graphalgorenderer.h"
#include <QLabel>

DFSWindow::DFSWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Depth-First Search");
    resize(400, 300);

    QLabel *label = new QLabel("This is where we teach DFS!", this);
    label->move(50, 50);

    GraphAlgoRenderer* renderer = new GraphAlgoRenderer(this);
    renderer->addNode("A", QPoint(100, 100));
    renderer->addNode("B", QPoint(200, 200));
    renderer->addNode("C", QPoint(300, 100));
    renderer->addEdge("A", "B");
    renderer->addEdge("B", "C");
    renderer->addEdge("A", "C");

    renderer->runTraversalAnimation({"A", "B", "C"});
    renderer->show();
}


