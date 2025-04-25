#ifndef GRAPHTRAVERSALGAMEWINDOW_H
#define GRAPHTRAVERSALGAMEWINDOW_H

#include <QWidget>
#include <QVector>
#include <QString>

class GraphAlgoRenderer;
class QLabel;
class QStackedWidget;
class QPushButton;

class GraphTraversalGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphTraversalGameWindow(QWidget *parent = nullptr);

signals:
    void playerFinished();

private slots:
    void handleBfsNodeClick(const QString &id);
    void handleDfsNodeClick(const QString &id);
    void handleRestart();
    void switchMode(bool toBfs);

private:
    void setupUI();
    void resetGame(bool bfsMode);
    QVector<QString> bfsOrder(const QString &start);
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
