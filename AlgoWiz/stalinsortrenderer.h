#ifndef STALINSORTRENDERER_H
#define STALINSORTRENDERER_H

#include "sortingalgorenderer.h"

class StalinSortRenderer : public sortingAlgoRenderer
{
public:
    StalinSortRenderer();

private:
    int currentStep = 1;
    void runSortStep();
    void startAnimation();
    void restoreList();
};

#endif // STALINSORTRENDERER_H
