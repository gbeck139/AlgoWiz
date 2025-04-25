/**
 * @file binarysearchrenderer.h
 * @author Woojin Lee, David Perry
 * @brief This file contains the declaration of the BinarySearchRenderer class to create the window for binarysearch algorithm.
 * @date 2025-04-24
 */

#ifndef BINARYSEARCHRENDERER_H
#define BINARYSEARCHRENDERER_H

#include "sortingalgorenderer.h"

class BinarySearchRenderer : public sortingAlgoRenderer
{
public:
    /**
     * @brief BinarySearchRenderer - constructs a binary search renderer and starts the animation.
     */
    BinarySearchRenderer();

private:
    /**
     * @brief low - The left boundary of the current search interval.
     */
    int low = 0;

    /**
     * @brief high - The right boundary of the current search interval.
     */
    int high = 0;

    /**
     * @brief target - The target value to search for.
     */
    int target = 0;

    /**
     * @brief stepInProgress - Check whether the binary serving algorithm is currently in progress.
     */
    bool stepInProgress = false;

    /**
     * @brief runSearchStep - helper to merge and handle the timing and finish logic after queuing merge steps.s
     */
    void runSearchStep();

    /**
     * @brief startAnimation - starts the animation and queues steps.
     */
    void startAnimation();
};

#endif // BINARYSEARCHRENDERER_H
