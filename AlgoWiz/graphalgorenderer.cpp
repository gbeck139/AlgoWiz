#include "graphalgorenderer.h"
#include <QPainter>
#include <QTimer>

GraphAlgoRenderer::GraphAlgoRenderer(QWidget* parent): QWidget(parent) {

   // Set up graph
    setMinimumSize(800, 800);
}

void GraphAlgoRenderer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw edges
    painter.setPen(QPen(Qt::black, 2));
    for (const Edge& edge : edges) {
        if (nodes.contains(edge.from) && nodes.contains(edge.to)) {
            QPoint from = nodes[edge.from].pos;
            QPoint to = nodes[edge.to].pos;
            painter.drawLine(from, to);
        }
    }

    // Draw nodes
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        const QString& id = it.key();
        const Node& node = it.value();

        painter.setBrush(node.color);
        painter.setPen(Qt::black);
        painter.drawEllipse(node.pos, 20, 20);
        painter.drawText(node.pos + QPoint(-25, -25), id);
    }
}

void GraphAlgoRenderer::runTraversalAnimation(const QVector<QString> &traversalOrder, int delayMs)
{
    for (int i = 0; i < traversalOrder.size(); ++i) {
        QTimer::singleShot(i * delayMs, this, [=]() {
            setNodeColor(traversalOrder[i], Qt::yellow);
        });
    }
}

void GraphAlgoRenderer::addNode(const QString& id, const QPoint& position){
    nodes[id] = Node{position, defaultColor};
}

void GraphAlgoRenderer::addEdge(const QString& from, const QString& to){
    edges.push_back({from, to});
}

void GraphAlgoRenderer::setNodeColor(const QString& id, const QColor& color){
    if (nodes.count(id) > 0){
        nodes[id].color = color;
    }
    update();
}

void GraphAlgoRenderer::createUnweightedGraph()
{
    addNode("A", QPoint(100, 300));
    addNode("B", QPoint(300, 300));
    addNode("C", QPoint(500, 300));
    addNode("D", QPoint(700, 300));
    addNode("E", QPoint(100, 450));
    addNode("F", QPoint(300, 450));
    addNode("G", QPoint(500, 450));
    addNode("H", QPoint(700, 450));
    addNode("I", QPoint(100, 600));
    addNode("J", QPoint(300, 600));
    addNode("K", QPoint(500, 600));
    addNode("L", QPoint(700, 600));
    addNode("M", QPoint(100, 750));
    addNode("N", QPoint(300, 750));
    addNode("O", QPoint(500, 750));
    addNode("P", QPoint(700, 750));


    addEdge("A", "B");
    addEdge("B", "C");
    addEdge("C", "D");
    addEdge("E", "F");
    addEdge("F", "G");
    addEdge("G", "H");
    addEdge("I", "J");
    addEdge("J", "K");
    addEdge("K", "L");
    addEdge("M", "N");
    addEdge("N", "O");
    addEdge("O", "P");
    addEdge("A", "E");
    addEdge("E", "I");
    addEdge("I", "M");
    addEdge("B", "F");
    addEdge("F", "J");
    addEdge("J", "N");
    addEdge("C", "G");
    addEdge("G", "K");
    addEdge("K", "O");
    addEdge("D", "H");
    addEdge("H", "L");
    addEdge("L", "P");
}

