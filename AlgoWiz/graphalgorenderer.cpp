#include "graphalgorenderer.h"
#include <QPainter>
#include <QTimer>

GraphAlgoRenderer::GraphAlgoRenderer(QWidget* parent): QWidget(parent) {

   // Set up graph
    setMinimumSize(600, 400);
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
        painter.drawText(node.pos + QPoint(-5, 35), id);
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

void GraphAlgoRenderer::displayNodes()
{
    update();
}
