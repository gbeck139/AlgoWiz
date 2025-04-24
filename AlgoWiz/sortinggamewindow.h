/**
 * @file sortinggamewindow.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the SortingGameWindow class and is used to display the sorting mini-game.
 * @date 2025-04-24
 */

#ifndef SORTINGGAMEWINDOW_H
#define SORTINGGAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "sortingalgorenderer.h"
#include "sortinggameplayer.h"

class SortingGameWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief SortingGameWindow - constructs a sorting game window.
     * @param parent - The parent widget
     */
    explicit SortingGameWindow(QWidget *parent = nullptr);

signals:
    /**
     * @brief difficultySelected - signal to be emitted when a difficulty is selected.
     * @param difficulty - the difficulty to select.
     */
    void difficultySelected(int difficulty);

private slots:
    /**
     * @brief handleDifficultySelection - handles logic for setting difficulty and swapping to respective algorithm.
     * @param difficulty - what difficulty was selected (0 = easy, 1 = normal, anything else = hard)
     */
    void handleDifficultySelection(int difficulty);

    /**
     * @brief checkAIProgress - helper that checks whether the ai algorithm has finished sorting or not.
     */
    void checkAIProgress();

    /**
     * @brief handlePlayerFinished - slot that handles logic for player finishing the game.
     */
    void handlePlayerFinished();

private:
    /**
     * @brief layout - vertical layout to organize the widget components of this widget game.
     */
    QVBoxLayout *layout;

    /**
     * @brief easySelection - button to select easy difficulty (v.s. insertion sort)
     */
    QPushButton *easySelection;

    /**
     * @brief mediumSelection - button to select normal difficulty (v.s. merge sort)
     */
    QPushButton *mediumSelection;

    /**
     * @brief hardSelection - button to select hard difficulty (v.s. stalin sort)
     */
    QPushButton *hardSelection;

    /**
     * @brief aiPlayer - the widget for the ai player.
     */
    sortingAlgoRenderer *aiPlayer;

    /**
     * @brief playerController - the widget that the player uses to sort the bars.
     */
    sortingGamePlayer *playerController;

    /**
     * @brief gameResultLabel - label to display the result of the game (whether ai or player won).
     */
    QLabel *gameResultLabel;

    /**
     * @brief aiFinished - whether the ai sorting algorithm has finished or not.
     */
    bool aiFinished = false;

    /**
     * @brief playerFinished - whether the player has finished or not.
     */
    bool playerFinished = false;
};

#endif // SORTINGGAMEWINDOW_H
