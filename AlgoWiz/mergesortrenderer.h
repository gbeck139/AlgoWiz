#ifndef MERGESORTRENDERER_H
#define MERGESORTRENDERER_H

#include "sortingalgorenderer.h"
#include <functional>
#include <queue>

class mergeSortRenderer : public sortingAlgoRenderer
{
public:
    mergeSortRenderer();

private:
    std::queue<std::function<void()>> mergeQueue;
    void startAnimation();
    void queueMergeSteps(int left, int right); // implemented recursively
    void merge(int left, int mid, int right);
    void runNextStep();
};

#endif // MERGESORTRENDERER_H
