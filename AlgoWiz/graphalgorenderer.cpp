/**
 * @file graphalgorenderer.cpp
 * @brief Implementation of the GraphAlgoRenderer class, handling graph drawing and traversal animations.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#include "graphalgorenderer.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

GraphAlgoRenderer::GraphAlgoRenderer(QWidget* parent): QWidget(parent) {

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void GraphAlgoRenderer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (nodes.isEmpty()) return;

    // Center the graph within the window
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    for (auto &kv : nodes) {
        const QPoint &p = kv.pos;
        minX = qMin(minX, p.x());
        minY = qMin(minY, p.y());
        maxX = qMax(maxX, p.x());
        maxY = qMax(maxY, p.y());
    }
    int graphW = maxX - minX;
    int graphH = maxY - minY;

    int shiftX = (width()  - graphW) / 2  -  minX;
    int shiftY = (height() - graphH) / 2  -  minY;

    painter.translate(shiftX, shiftY);

    painter.setPen(QPen(Qt::white, 4));

    QFont font = painter.font();
    font.setPointSize(14);
    font.setBold(true);
    painter.setFont(font);

    // Draw edges
    for (const Edge& edge : edges) {
        if (nodes.contains(edge.from) && nodes.contains(edge.to)) {
            painter.setPen(QPen(Qt::white, 4));
            QPoint from = nodes[edge.from].pos;
            QPoint to = nodes[edge.to].pos;
            if (edge.weighted){
                QPoint mid = (from + to) / 2;
                QPoint labelPos = mid + QPoint(0, -10);
                painter.drawText(labelPos, QString::number(edge.weight));
            }
            painter.setPen(QPen(edge.color, 4));
            painter.drawLine(from, to);
        }
    }

    // Draw nodes
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {

        QFont font = painter.font();
        font.setPointSize(14);
        font.setBold(true);
        painter.setFont(font);

        const QString& id = it.key();
        const Node& node = it.value();

        painter.setBrush(node.color);
        painter.setPen(Qt::white);
        painter.drawText(node.pos + QPoint(-25, -25), id);
        painter.setPen(Qt::black);
        painter.drawEllipse(node.pos, 20, 20);
        if (node.hasValue){
            if(node.value == INT_MAX){
                painter.drawText(node.pos+ QPoint(-7, 5), "∞");
            }else{
                painter.drawText(node.pos+ QPoint(-7, 5), QString::number(node.value));
            }
        }
    }
}

void GraphAlgoRenderer::runTraversalAnimation(const QVector<QString> &traversalOrder, int delayMs)
{
    // Read the traversal inputs
    for (int i = 0; i < traversalOrder.size(); ++i) {
        if(traversalOrder[i].startsWith("_")){
            QString edge = traversalOrder[i].split("_")[1];
            QTimer::singleShot(i * delayMs, this, [=]() {
                setEdgeColor(edge.toInt(), QColor("#1E90FF"));  // Blue color for edges
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
                setNodeColor(traversalOrder[i], QColor("#06FFFF"));  // Cyan color for nodes
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

    addNode("D", QPoint(100, 600), true, 5);
    addNode("E", QPoint(600, 600), true, 2);
    addEdge("D", "E", true, 6);
}

void GraphAlgoRenderer::createUnweightedGraph()
{
    // Adds nodes and edges for an unweighted example graph
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

    // Connecting edges
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
    // Adds nodes and edges for a weighted example graph
    addNode("B", QPoint(300, 450), true, INT_MAX);
    addNode("D", QPoint(300, 750), true, INT_MAX);
    addNode("F", QPoint(600, 750), true, INT_MAX);
    addNode("A", QPoint(150, 600), true, 0);
    addNode("C", QPoint(750, 600), true, INT_MAX);
    addNode("E", QPoint(600, 450), true, INT_MAX);

    addEdge("A", "B", true, 2);
    addEdge("A", "D", true, 8);
    addEdge("B", "D", true, 5);
    addEdge("B", "E", true, 6);
    addEdge("D", "E", true, 3);
    addEdge("D", "F", true, 2);
    addEdge("F", "E", true, 1);
    addEdge("F", "C", true, 3);
    addEdge("E", "C", true, 9);
}

void GraphAlgoRenderer::mousePressEvent(QMouseEvent *ev)
{
    // Adjust mouse click position relative to the graph's centered position
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    for (auto &kv : nodes) {
        const QPoint &p = kv.pos;
        minX = qMin(minX, p.x());
        minY = qMin(minY, p.y());
        maxX = qMax(maxX, p.x());
        maxY = qMax(maxY, p.y());
    }
    int graphW = maxX - minX;
    int graphH = maxY - minY;

    int shiftX = (width() - graphW) / 2 - minX;
    int shiftY = (height() - graphH) / 2 - minY;

    QPoint adjustedPos = ev->pos() - QPoint(shiftX, shiftY);

    // Check if a node was clicked
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (QLineF(adjustedPos, it.value().pos).length() <= 20) {
            emit nodeClicked(it.key());
            break;
        }
    }
}
