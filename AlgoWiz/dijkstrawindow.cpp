#include "dijkstrawindow.h"
#include "graphalgorenderer.h"
#include <QLabel>

DijkstraWindow::DijkstraWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Dijkstra's");
    resize(800, 800);

    QLabel *label = new QLabel("This is where we teach Dijkstra's!", this);
    label->move(50, 50);

    GraphAlgoRenderer* renderer = new GraphAlgoRenderer(this);

    renderer->createWeightedGraph();

    renderer->runTraversalAnimation({"A", "_1", "_0", "B", "_2", "_3", "D", "_5", "_4", "E", "_6", "_8", "F", "_7", "C"});
}
