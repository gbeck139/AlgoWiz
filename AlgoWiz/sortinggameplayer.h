#ifndef SORTINGGAMEPLAYER_H
#define SORTINGGAMEPLAYER_H

#include "sortingalgorenderer.h"
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

class sortingGamePlayer : public sortingAlgoRenderer
{
    Q_OBJECT
public:
    explicit sortingGamePlayer(QWidget *parent = nullptr);
    bool isSorted();

signals:
    void playerFinished();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int draggedBarIndex = -1;
    QPoint dragStartPosition;
    bool dragging = false;
    int targetIndex = -1;
    void resetGame();
    int getBarIndexAt(const QPoint &pos);
    bool checkIfSorted();
};

#endif // SORTINGGAMEPLAYER_H
