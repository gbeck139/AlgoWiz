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
            if (edge.weighted){
                QPoint mid = (from + to) / 2;
                QPoint labelPos = mid + QPoint(0, -10);
                painter.drawText(labelPos, QString::number(edge.weight));
            }
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

void GraphAlgoRenderer::addEdge(const QString& from, const QString& to, bool weighted, int weight){
    edges.push_back({from, to, weighted, weight});
}

void GraphAlgoRenderer::setNodeColor(const QString& id, const QColor& color){
    if (nodes.count(id) > 0){
        nodes[id].color = color;
    }
    update();
}

void GraphAlgoRenderer::createTheoryGraph(){
    addNode("A", QPoint(100, 300));
    addNode("B", QPoint(500, 300));
    addNode("C", QPoint(600, 300));

    addEdge("C", "B", false);

    addNode("D", QPoint(100, 600));
    addNode("E", QPoint(600, 600));

    addEdge("D", "E", true, 6);
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


    addEdge("A", "B", false);
    addEdge("B", "C", false);
    addEdge("C", "D", false);
    addEdge("E", "F", false);
    addEdge("F", "G", false);
    addEdge("G", "H", false);
    addEdge("I", "J", false);
    addEdge("J", "K", false);
    addEdge("K", "L", false);
    addEdge("M", "N", false);
    addEdge("N", "O", false);
    addEdge("O", "P", false);
    addEdge("A", "E", false);
    addEdge("E", "I", false);
    addEdge("I", "M", false);
    addEdge("B", "F", false);
    addEdge("F", "J", false);
    addEdge("J", "N", false);
    addEdge("C", "G", false);
    addEdge("G", "K", false);
    addEdge("K", "O", false);
    addEdge("D", "H", false);
    addEdge("H", "L", false);
    addEdge("L", "P", false);
}

