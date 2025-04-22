#include "graphalgorenderer.h"
#include <QPainter>
#include <QTimer>

GraphAlgoRenderer::GraphAlgoRenderer(QWidget* parent): QWidget(parent) {

   // Set up graph
    setMinimumSize(1200, 1200);

}

void GraphAlgoRenderer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int shiftX = width()  / 6;   // e.g. one‑sixth of total canvas
    const int shiftY = height() / 8;   // e.g. one‑eighth of total canvas

    painter.translate(shiftX, shiftY);

    // Draw edges
    painter.setPen(QPen(Qt::white, 2));
    for (const Edge& edge : edges) {
        if (nodes.contains(edge.from) && nodes.contains(edge.to)) {
            painter.setPen(QPen(Qt::black, 2));
            QPoint from = nodes[edge.from].pos;
            QPoint to = nodes[edge.to].pos;
            if (edge.weighted){
                QPoint mid = (from + to) / 2;
                QPoint labelPos = mid + QPoint(0, -10);
                painter.drawText(labelPos, QString::number(edge.weight));
            }
            painter.setPen(QPen(edge.color, 2));
            painter.drawLine(from, to);
        }
    }

    // Draw nodes
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        const QString& id = it.key();
        const Node& node = it.value();

        painter.setBrush(node.color);
        painter.setPen(Qt::white);
        painter.drawEllipse(node.pos, 20, 20);
        painter.drawText(node.pos + QPoint(-25, -25), id);
        if (node.hasValue){
            if(node.value == INT_MAX){
                painter.drawText(node.pos+ QPoint(-5, 5), "∞");
            }else{
                painter.drawText(node.pos+ QPoint(-5, 5), QString::number(node.value));
            }
        }
    }
}

void GraphAlgoRenderer::runTraversalAnimation(const QVector<QString> &traversalOrder, int delayMs)
{
    for (int i = 0; i < traversalOrder.size(); ++i) {
        if(traversalOrder[i].startsWith("_")){
            QTimer::singleShot(i * delayMs, this, [=]() {
                setEdgeColor(traversalOrder[i].right(1).toInt(), Qt::yellow);
            });
        }else if(traversalOrder[i].startsWith(".")){
            QStringList parts = traversalOrder[i].split(".");
            QString nodeId = parts[1];
            int value = parts[2].toInt();
            QTimer::singleShot(i * delayMs, this, [=]() {
                setNodeValue(nodeId, value);
            });
        }else {
            QTimer::singleShot(i * delayMs, this, [=]() {
                setNodeColor(traversalOrder[i], Qt::yellow);
            });
        }
    }
}

void GraphAlgoRenderer::addNode(const QString& id, const QPoint& position, bool hasValue, int value){
    nodes[id] = Node{position, defaultColor, hasValue, value};
}

void GraphAlgoRenderer::addEdge(const QString& from, const QString& to, bool weighted, int weight){
    edges.push_back({from, to, weighted, weight});
}

void GraphAlgoRenderer::setNodeValue(const QString& id, int value){
    nodes[id].value = value;
    update();
}

void GraphAlgoRenderer::setNodeColor(const QString& id, const QColor& color){
    if (nodes.count(id) > 0){
        nodes[id].color = color;
    }
    update();
}

void GraphAlgoRenderer::setEdgeColor(int id, const QColor& color){
    if(id > -1 && id < edges.length()){
        edges[id].color = color;
        update();
    }
}

void GraphAlgoRenderer::createTheoryGraph(){
    addNode("A", QPoint(100, 300), false);
    addNode("B", QPoint(500, 300), false);
    addNode("C", QPoint(600, 300), false);

    addEdge("C", "B", false);

    addNode("D", QPoint(100, 600), false);
    addNode("E", QPoint(600, 600), false);

    addEdge("D", "E", true, 6);
}

void GraphAlgoRenderer::createUnweightedGraph()
{
    addNode("A", QPoint(100, 300), false);
    addNode("B", QPoint(300, 300), false);
    addNode("C", QPoint(500, 300), false);
    addNode("D", QPoint(700, 300), false);
    addNode("E", QPoint(100, 450), false);
    addNode("F", QPoint(300, 450), false);
    addNode("G", QPoint(500, 450), false);
    addNode("H", QPoint(700, 450), false);
    addNode("I", QPoint(100, 600), false);
    addNode("J", QPoint(300, 600), false);
    addNode("K", QPoint(500, 600), false);
    addNode("L", QPoint(700, 600), false);
    addNode("M", QPoint(100, 750), false);
    addNode("N", QPoint(300, 750), false);
    addNode("O", QPoint(500, 750), false);
    addNode("P", QPoint(700, 750), false);


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

void GraphAlgoRenderer::createWeightedGraph()
{
    // https://www.youtube.com/watch?v=bZkzH5x0SKU
    // Add Nodes (coordinates chosen to reflect top row = 1,3,5 and bottom row = 0,2,4)
    addNode("B", QPoint(200, 300), true, INT_MAX);  // Top-left
    addNode("D", QPoint(200, 500), true, INT_MAX);  // Top-middle
    addNode("F", QPoint(400, 500), true, INT_MAX);  // Top-right
    addNode("A", QPoint(100, 400), true, 0);  // Bottom-left
    addNode("C", QPoint(500, 400), true, INT_MAX);  // Bottom-middle
    addNode("E", QPoint(400, 300), true, INT_MAX);  // Bottom-right

    // Add Edges (undirected, with weights taken from the diagram)
    addEdge("A", "B", true, 2); // 2
    addEdge("A", "D", true, 8); // 1
    addEdge("B", "D", true, 5); // 3
    addEdge("B", "E", true, 6); // 4
    addEdge("D", "E", true, 3); // 6
    addEdge("D", "F", true, 2); // 5
    addEdge("F", "E", true, 1); // 7
    addEdge("F", "C", true, 3); // 9
    addEdge("E", "C", true, 9); // 8
}

