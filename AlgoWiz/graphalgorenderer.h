#ifndef GRAPHALGORENDERER_H
#define GRAPHALGORENDERER_H

#include <QWidget>

class GraphAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    explicit GraphAlgoRenderer(QWidget* parent = nullptr);

    void addNode(const QString& id, const QPoint& position);
    void addEdge(const QString& from, const QString& to);
    void setNodeColor(const QString& id, const QColor& color);

    void runTraversalAnimation(const QVector<QString>& traversalOrder, int delayMs = 300);

    void displayNodes();

protected:
    void paintEvent(QPaintEvent* event) override;

    struct Node {
        QPoint pos;
        QColor color = Qt::white;
    };

    struct Edge {
        QString from;
        QString to;
    };

    QMap<QString, Node> nodes;
    QVector<Edge> edges;

    const QRgb orange = 0xff8c00;
    QColor defaultColor = QColor(orange);
};

#endif // GRAPHALGORENDERER_H
