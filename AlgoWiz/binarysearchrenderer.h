#ifndef BINARYSEARCHRENDERER_H
#define BINARYSEARCHRENDERER_H

#include "sortingalgorenderer.h"

class BinarySearchRenderer : public sortingAlgoRenderer
{
public:
    BinarySearchRenderer();

private:
    int low = 0;
    int high = 0;
    int target = 0;
    bool stepInProgress = false;
    void runSearchStep();
    void startAnimation();
};

#endif // BINARYSEARCHRENDERER_H
