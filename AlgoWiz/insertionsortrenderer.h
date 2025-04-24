/**
 * @file insertionsortrenderer.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the insertion sort renderer class.
 * @date 2025-04-24
 */

#ifndef INSERTIONSORTRENDERER_H
#define INSERTIONSORTRENDERER_H

#include "sortingalgorenderer.h"

/**
 * @brief The InsertionSortRenderer class is a class that extends sortingAlgoRenderer.
 * Used to render the insertion sort animation.
 */
class InsertionSortRenderer : public sortingAlgoRenderer
{
public:
    /**
     * @brief InsertionSortRenderer constructor
     */
    InsertionSortRenderer();

private:
    /**
     * @brief The current step of the insertion sort
     */
    int currentStep = 1;
    /**
     * @brief The while step of the insertion sort
     */
    int whileStep = 0;

    /**
     * @brief Whether the step is in progress
     */
    bool stepInProgress = false; // false when we move to next step in for loop

    /**
     * @brief Runs the next step of the insertion sort
     */
    void runSortStep();

    /**
     * @brief Starts the animation
     */
    void startAnimation();
};

#endif // INSERTIONSORTRENDERER_H
