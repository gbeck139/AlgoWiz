#ifndef GRAPHBFSGAMEWINDOW_H
#define GRAPHBFSGAMEWINDOW_H

#include <QWidget>
#include "graphalgorenderer.h"

class QLabel;

class GraphBFSGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GraphBFSGameWindow(QWidget *parent = nullptr);

signals:
    void playerFinished();          // same signal name as sorting game

private slots:
    void handleClick(const QString &id);

private:
    void resetGame();
    QVector<QString> bfsOrder(const QString &start);
    GraphAlgoRenderer *renderer;
    QLabel *info;
    QVector<QString> correctOrder;  // canonical BFS sequence
    int nextIndex = 0;              // where player is in the sequence
};

#endif // GRAPHBFSGAMEWINDOW_H
