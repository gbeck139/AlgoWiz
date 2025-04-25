#ifndef GRAPHALGORENDERER_H
#define GRAPHALGORENDERER_H

#include <QWidget>

class GraphAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    explicit GraphAlgoRenderer(QWidget* parent = nullptr);

    void addNode(const QString& id, const QPoint& position, bool hasValue, int value = 0);
    void addEdge(const QString& from, const QString& to, bool weighted, int weight = 0);
    void setNodeColor(const QString& id, const QColor& color);
    void setNodeValue(const QString& id, int value);
    void setEdgeColor(int id, const QColor& color);
    void createUnweightedGraph();
    void createTheoryGraph();
    void createWeightedGraph();

    void runTraversalAnimation(const QVector<QString>& traversalOrder, int delayMs = 1000);

    struct Node {
        QPoint pos;
        QColor color = Qt::black;
        bool hasValue;
        int value;
    };

    struct Edge {
        QString from;
        QString to;
        bool weighted;
        int weight;
        QColor color = Qt::white;
    };

    QMap<QString, Node> nodes;
    QVector<Edge> edges;


signals:
    void nodeClicked(const QString &id);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *ev) override;


    const QRgb orange = 0xff8c00;
    QColor defaultColor = QColor(QColorConstants::Svg::white);
};

#endif // GRAPHALGORENDERER_H
