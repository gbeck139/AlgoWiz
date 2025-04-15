#ifndef INSERTIONSORTRENDERER_H
#define INSERTIONSORTRENDERER_H

#include "sortingalgorenderer.h"

class InsertionSortRenderer : public sortingAlgoRenderer
{
public:
    InsertionSortRenderer();

private:
    int currentStep = 1;
    int whileStep = 0;
    bool stepInProgress = false; // false when we move to next step in for loop
    void runSortStep();
    void startAnimation();
};

#endif // INSERTIONSORTRENDERER_H
