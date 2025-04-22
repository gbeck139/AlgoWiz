#include "sortinggameplayer.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QDebug>

sortingGamePlayer::sortingGamePlayer(QWidget *parent)
    : sortingAlgoRenderer(parent, false)
{
    // clear the vector, loop through
    bars.clear();

    // put 20 bar structs in the bars vector
    for (int i = 5; i <= 25; i++) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 25; // hardcoded to our loop

    setWindowTitle("Sorting Game");
    resize(600, 500);
    resetGame();
}

void sortingGamePlayer::resetGame()
{
    // reset all bar colors
    for (size_t i = 0; i < bars.size(); ++i) {
        setBarColor(i, defaultColor);
    }

    // shuffle bars
    shuffle();
    update();
}

void sortingGamePlayer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        draggedBarIndex = getBarIndexAt(event->pos());
        if (draggedBarIndex != -1)
        {
            dragStartPosition = event->pos();
            dragging = true;
            setBarColor(draggedBarIndex, Qt::red); // highlight user slected bar
            update();
        }
    }
}

void sortingGamePlayer::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && draggedBarIndex != -1)
    {
        // find out which position we're "hovering" over
        targetIndex = getBarIndexAt(event->pos());

        for (size_t i = 0; i < bars.size(); ++i)
        {
            if (i == draggedBarIndex)
            {
                // highlight selected bar
                setBarColor(i, Qt::red);
            }
            else if (i == targetIndex)
            {
                // highlight where we would be potentially placing the bar
                setBarColor(i, Qt::blue);
            }
            else
            {
                // reset other bars to our default color
                setBarColor(i, defaultColor);
            }
        }
        update();
    }
}

void sortingGamePlayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (dragging && draggedBarIndex != -1)
    {
        targetIndex = getBarIndexAt(event->pos());

        // we can only move if target is valid and we're actually moving it somewhere
        if (targetIndex != -1 && targetIndex != draggedBarIndex)
        {
            // move bar struct
            bar temp = bars[draggedBarIndex];

            // shift everything accordingly
            if (targetIndex > draggedBarIndex)
            {
                // this is for shifting right
                for (int i = draggedBarIndex; i < targetIndex; ++i)
                {
                    bars[i] = bars[i + 1];
                }
            }
            else
            {
                // shifting left
                for (int i = draggedBarIndex; i > targetIndex; --i)
                {
                    bars[i] = bars[i - 1];
                }
            }

            // drop bar at target
            bars[targetIndex] = temp;
        }

        // reset bar color
        for (size_t i = 0; i < bars.size(); ++i)
        {
            setBarColor(i, defaultColor);
        }

        // check if sorted, if sorted, we turn it green and emit a signal
        if (checkIfSorted())
        {
            for (size_t i = 0; i < bars.size(); ++i)
            {
                setBarColor(i, Qt::green);
            }
            emit playerFinished();
        }

        dragging = false;
        draggedBarIndex = -1;
        targetIndex = -1;
        update();
    }
}

int sortingGamePlayer::getBarIndexAt(const QPoint &pos)
{
    if (bars.empty())
        return -1;

    double barWidth = static_cast<double>(width()) / bars.size();
    int index = pos.x() / barWidth;

    if (index >= 0 && index < static_cast<int>(bars.size()))
    {
        return index;
    }

    return -1;
}

bool sortingGamePlayer::checkIfSorted()
{
    for (size_t i = 1; i < bars.size(); ++i)
    {
        if (bars[i - 1].val > bars[i].val)
        {
            return false;
        }
    }
    return true;
}
