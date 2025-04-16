#include "graphtheorywindow.h"
#include "graphalgorenderer.h"
#include <QLabel>


GraphTheoryWindow::GraphTheoryWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Graph Theory");
    resize(800, 800);

    QLabel *label = new QLabel("This is where we teach Graph Theory!", this);
    label->move(50, 50);

    GraphAlgoRenderer* renderer = new GraphAlgoRenderer(this);

    renderer->createTheoryGraph();
}
