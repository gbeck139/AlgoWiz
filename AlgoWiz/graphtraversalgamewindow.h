/**
 * @file GraphTraversalGameWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the GraphTraversalGameWindow class, which provides an interactive game for practicing BFS and DFS traversals.
 * @date 2025-04-25
 */


#ifndef GRAPHTRAVERSALGAMEWINDOW_H
#define GRAPHTRAVERSALGAMEWINDOW_H

#include <QWidget>
#include <QVector>
#include <QString>

class GraphAlgoRenderer;
class QLabel;
class QStackedWidget;
class QPushButton;

/**
 * @class GraphTraversalGameWindow
 * @brief GraphTraversalGameWindow provides a QWidget-based game interface where users can practice BFS and DFS graph traversals interactively.
 */
class GraphTraversalGameWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for GraphTraversalGameWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    explicit GraphTraversalGameWindow(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the player completes the traversal.
     */
    void playerFinished();

private slots:
    /**
     * @brief Slot to handle node clicks in BFS mode.
     * @param id - the ID of the clicked node.
     */
    void handleBfsNodeClick(const QString &id);

    /**
     * @brief Slot to handle node clicks in DFS mode.
     * @param id - the ID of the clicked node.
     */
    void handleDfsNodeClick(const QString &id);

    /**
     * @brief Slot to handle game restart.
     */
    void handleRestart();

    /**
     * @brief Slot to switch between BFS and DFS modes.
     * @param toBfs - true to switch to BFS mode, false for DFS mode.
     */
    void switchMode(bool toBfs);

private:
    /**
     * @brief Sets up the user interface layout and widgets.
     */
    void setupUI();

    /**
     * @brief Resets the game state and graph to the initial configuration.
     * @param bfsMode - true for BFS mode, false for DFS mode.
     */
    void resetGame(bool bfsMode);

    /**
     * @brief Generates the BFS traversal order starting from a given node.
     * @param start - the starting node ID.
     * @return QVector of node IDs in BFS order.
     */
    QVector<QString> bfsOrder(const QString &start);

    /**
     * @brief Generates the DFS traversal order starting from a given node.
     * @param start - the starting node ID.
     * @return QVector of node IDs in DFS order.
     */
    QVector<QString> dfsOrder(const QString &start);

    GraphAlgoRenderer *bfsRenderer;
    GraphAlgoRenderer *dfsRenderer;
    QLabel *bfsLabel;
    QLabel *dfsLabel;
    QStackedWidget *stackedWidget;
    QPushButton *bfsButton;
    QPushButton *dfsButton;
    QPushButton *restartButton;

    QVector<QString> bfsList;
    QVector<QString> dfsList;
    int bfsIndex;
    int dfsIndex;
    bool currentMode; // true = BFS, false = DFS
};

#endif // GRAPHTRAVERSALGAMEWINDOW_H
