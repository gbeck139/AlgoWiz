/**
 * @file mergesortrenderer.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the mergeSortRenderer class to animate merge sort.
 * @date 2025-04-24
 */

#ifndef MERGESORTRENDERER_H
#define MERGESORTRENDERER_H

#include "sortingalgorenderer.h"
#include <functional>
#include <queue>

class mergeSortRenderer : public sortingAlgoRenderer
{
public:
    /**
     * @brief mergeSortRenderer - constructs a merge sort renderer and starts the animation automatically.
     */
    mergeSortRenderer();

private:
    /**
     * @brief mergeQueue - queue of merge steps to call - simulates a recursive call stack.
     */
    std::queue<std::function<void()>> mergeQueue;

    /**
     * @brief startAnimation - starts the animation and queues steps.
     */
    void startAnimation();

    /**
     * @brief queueMergeSteps - recursively determines all the steps for mergesort to queue, simulating a recursive call stack.
     * @param left - left of the subarray for mergesort.
     * @param right - right of the subarray for mergesort.
     */
    void queueMergeSteps(int left, int right);

    /**
     * @brief merge - merges the subarrays (left -> mid, mid -> right) and animates, shows blue on changes.
     * @param left - the left edge of the subarrays to merge.
     * @param mid - the center of the subarrays.
     * @param right - the right edge of the subarrays.
     */
    void merge(int left, int mid, int right);

    /**
     * @brief runNextStep - helper to merge and handle the timing and finish logic after queuing merge steps.s
     */
    void runNextStep();
};

#endif // MERGESORTRENDERER_H
