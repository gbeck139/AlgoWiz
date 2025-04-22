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

    renderer->runTraversalAnimation({"A", "_0", ".B.2", "_1", ".D.8",
                                     "B", "_2", ".D.7", "_3", ".E.8",
                                     "D", "_5", ".F.9", "_4",
                                     "E", "_6", "_8", ".C.17",
                                     "F", "_7", "C"});
}
