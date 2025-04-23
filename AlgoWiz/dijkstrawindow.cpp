#include "dijkstrawindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

DijkstraWindow::DijkstraWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Dijkstra’s Algorithm");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createWeightedGraph();
    renderer->runTraversalAnimation({
        "A","_0",".B.2","_1",".D.8",
        "B","_2",".D.7","_3",".E.8",
        "D","_5",".F.9","_4",
        "E","_6","_8",".C.17",
        "F","_7","C"});

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
