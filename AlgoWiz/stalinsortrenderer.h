/**
 * @file stalinsortrenderer.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the Stalin sort renderer class.
 * @date 2025-04-24
 */

#ifndef STALINSORTRENDERER_H
#define STALINSORTRENDERER_H

#include "sortingalgorenderer.h"

/**
 * @brief The StalinSortRenderer class is a class that extends sortingAlgoRenderer.
 * Used to render the Stalin sort animation.
 */
class StalinSortRenderer : public sortingAlgoRenderer
{
public:
    /**
     * @brief StalinSortRenderer constructor
     */
    StalinSortRenderer();

private:
    /**
     * @brief The current step of the Stalin sort
     */
    int currentStep = 1;
    /**
     * @brief Runs the next step of the Stalin sort
     */
    void runSortStep();
    /**
     * @brief Starts the animation
     */
    void startAnimation();
    /**
     * @brief Restores the list
     */
    void restoreList();
};

#endif // STALINSORTRENDERER_H
