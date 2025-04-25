#ifndef GRAPHTRAVERSALGAMEWINDOW_H
#define GRAPHTRAVERSALGAMEWINDOW_H

#include <QWidget>
#include <QVector>
#include <QString>

class GraphAlgoRenderer;
class QLabel;

class GraphTraversalGameWindow : public QWidget {
    Q_OBJECT
public:
    explicit GraphTraversalGameWindow(QWidget *parent = nullptr);

signals:
    void playerFinished();

private:
    void setupTabs();
    void resetGame(bool bfsMode);
    QVector<QString> bfsOrder(const QString &start);
    QVector<QString> dfsOrder(const QString &start);

    GraphAlgoRenderer *bfsRenderer;
    GraphAlgoRenderer *dfsRenderer;
    QLabel *bfsLabel;
    QLabel *dfsLabel;

    QVector<QString> bfsList;
    QVector<QString> dfsList;
    int bfsIndex;
    int dfsIndex;
};

#endif // GRAPHTRAVERSALGAMEWINDOW_H
