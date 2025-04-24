/**
 * @file sortinggameplayer.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the sorting game player class.
 * @date 2025-04-24
 */

#ifndef SORTINGGAMEPLAYER_H
#define SORTINGGAMEPLAYER_H

#include "sortingalgorenderer.h"
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief The sortingGamePlayer class is a class that extends sortingAlgoRenderer.
 * Used to play the sorting game.
 */
class sortingGamePlayer : public sortingAlgoRenderer
{
    Q_OBJECT
public:
    /**
     * @brief sortingGamePlayer constructor
     * @param parent The parent widget
     */
    explicit sortingGamePlayer(QWidget *parent = nullptr);

    /**
     * @brief Resets the game
     */
    void resetGame();

signals:
    /**
     * @brief Emitted when the player finishes the game
     */
    void playerFinished();

protected:
    /**
     * @brief Handles mouse press events
     * @param event The mouse event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse move events
     * @param event The mouse event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse release events
     * @param event The mouse event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    /**
     * @brief The index of the bar that is being dragged
     */
    int draggedBarIndex = -1;

    /**
     * @brief The start position of the drag
     */
    QPoint dragStartPosition;

    /**
     * @brief Whether the bar is being dragged
     */
    bool dragging = false;

    /**
     * @brief The index of the bar that we are potentially placing the dragged bar on
     */
    int targetIndex = -1;

    /**
     * @brief Gets the index of the bar at the given position
     * @param pos The position
     * @return The index of the bar at the given position
     */
    int getBarIndexAt(const QPoint &pos);

    /**
     * @brief Checks if the bars are sorted
     * @return True if the bars are sorted, false otherwise
     */
    bool checkIfSorted();
};

#endif // SORTINGGAMEPLAYER_H
