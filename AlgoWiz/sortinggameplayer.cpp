#include "sortinggameplayer.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QDebug>

sortingGamePlayer::sortingGamePlayer(QWidget *parent)
    : sortingAlgoRenderer(parent, false)
{
    setWindowTitle("Sorting Game");
    resize(600, 500);
    resetGame();
}

void sortingGamePlayer::resetGame()
{
    // Reset the bar colors
    for (size_t i = 0; i < bars.size(); ++i)
    {
        setBarColor(i, defaultColor);
    }

    // Shuffle the bars
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
            setBarColor(draggedBarIndex, Qt::red); // Highlight selected bar
            update();
        }
    }
}

void sortingGamePlayer::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && draggedBarIndex != -1)
    {
        // Calculate which position we're hovering over
        targetIndex = getBarIndexAt(event->pos());

        // Update visual feedback
        for (size_t i = 0; i < bars.size(); ++i)
        {
            if (i == draggedBarIndex)
            {
                // Keep selected bar highlighted
                setBarColor(i, Qt::red);
            }
            else if (i == targetIndex)
            {
                // Highlight potential drop target
                setBarColor(i, Qt::blue);
            }
            else
            {
                // Reset other bars to default
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

        // Only move if we have a valid target and it's different from source
        if (targetIndex != -1 && targetIndex != draggedBarIndex)
        {
            // Move the bar to the new position
            bar temp = bars[draggedBarIndex];

            // Shift bars between source and target
            if (targetIndex > draggedBarIndex)
            {
                // Moving right
                for (int i = draggedBarIndex; i < targetIndex; ++i)
                {
                    bars[i] = bars[i + 1];
                }
            }
            else
            {
                // Moving left
                for (int i = draggedBarIndex; i > targetIndex; --i)
                {
                    bars[i] = bars[i - 1];
                }
            }

            // Place dragged bar at target position
            bars[targetIndex] = temp;
        }

        // Reset all bars to default color
        for (size_t i = 0; i < bars.size(); ++i)
        {
            setBarColor(i, defaultColor);
        }

        // Check if the array is sorted
        if (checkIfSorted())
        {
            for (size_t i = 0; i < bars.size(); ++i)
            {
                setBarColor(i, Qt::green); // All green when sorted
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

bool sortingGamePlayer::isSorted()
{
    return checkIfSorted();
}
