#include "graphtheorywindow.h"
#include "graphalgorenderer.h"
#include <QVBoxLayout>
#include <QLabel>

GraphTheoryWindow::GraphTheoryWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Graph Theory");

    auto *renderer = new GraphAlgoRenderer(this);
    renderer->createTheoryGraph();

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(renderer);
}
