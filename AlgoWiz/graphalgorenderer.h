/**
 * @file GraphAlgoRenderer.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the GraphAlgoRenderer class, which provides graph visualization and traversal animations.
 * @date 2025-04-25
 */

#ifndef GRAPHALGORENDERER_H
#define GRAPHALGORENDERER_H

#include <QWidget>

/**
 * @class GraphAlgoRenderer
 * @brief GraphAlgoRenderer class handles the rendering and animation of graph algorithms including node and edge manipulation.
 */
class GraphAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for GraphAlgoRenderer.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    explicit GraphAlgoRenderer(QWidget* parent = nullptr);

    /**
     * @brief Adds a node to the graph.
     * @param id - identifier of the node.
     * @param position - position of the node.
     * @param hasValue - flag indicating if the node holds a value.
     * @param value - the value held by the node (optional, defaults to 0).
     */
    void addNode(const QString& id, const QPoint& position, bool hasValue, int value = 0);

    /**
     * @brief Adds an edge to the graph.
     * @param from - source node ID.
     * @param to - destination node ID.
     * @param weighted - flag indicating if the edge is weighted.
     * @param weight - weight of the edge (optional, defaults to 0).
     */
    void addEdge(const QString& from, const QString& to, bool weighted, int weight = 0);

    /**
     * @brief Sets the color of a node.
     * @param id - the node identifier.
     * @param color - the color to set.
     */
    void setNodeColor(const QString& id, const QColor& color);

    /**
     * @brief Sets the value of a node.
     * @param id - the node identifier.
     * @param value - the value to assign.
     */
    void setNodeValue(const QString& id, int value);

    /**
     * @brief Sets the color of an edge.
     * @param id - the edge index in the edges vector.
     * @param color - the color to set.
     */
    void setEdgeColor(int id, const QColor& color);

    /**
     * @brief Creates a default unweighted graph.
     */
    void createUnweightedGraph();

    /**
     * @brief Creates a graph for theoretical demonstrations.
     */
    void createTheoryGraph();

    /**
     * @brief Creates a weighted graph.
     */
    void createWeightedGraph();

    /**
     * @brief Runs an animated traversal sequence on the graph.
     * @param traversalOrder - the order of node/edge visits.
     * @param delayMs - delay between steps in milliseconds (optional, defaults to 1000 ms).
     */
    void runTraversalAnimation(const QVector<QString>& traversalOrder, int delayMs = 1000);

    /**
     * @struct Node
     * @brief Represents a graph node with position, color, value, and value existence flag.
     */
    struct Node {
        QPoint pos;
        QColor color = Qt::black;
        bool hasValue;
        int value;
    };

    /**
     * @struct Edge
     * @brief Represents an edge between two nodes, with optional weight and color.
     */
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
    /**
     * @brief Signal emitted when a node is clicked.
     * @param id - the ID of the clicked node.
     */
    void nodeClicked(const QString &id);

protected:
    /**
     * @brief Handles the paint event to render the graph.
     * @param event - the paint event.
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief Handles mouse press events for node selection.
     * @param ev - the mouse event.
     */
    void mousePressEvent(QMouseEvent *ev) override;

    const QRgb orange = 0xff8c00;
    QColor defaultColor = QColor(QColorConstants::Svg::white);
};

#endif // GRAPHALGORENDERER_H
