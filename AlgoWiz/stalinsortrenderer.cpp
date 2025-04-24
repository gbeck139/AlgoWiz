/**
 * @file stalinsortrenderer.cpp
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the implementation of the Stalin sort renderer class.
 * @date 2025-04-24
 */

#include "stalinsortrenderer.h"
#include <QTimer>

StalinSortRenderer::StalinSortRenderer()
{
    startAnimation();
}

void StalinSortRenderer::restoreList()
{
    bars = std::vector<bar>();

    for (int i = 1; i <= 20; i++)
    {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 20; // hardcoded to our loop
}

void StalinSortRenderer::startAnimation()
{
    shuffle();
    setBarColor(0, Qt::red);
    update();
    runSortStep();
}

void StalinSortRenderer::runSortStep()
{
    if (currentStep >= (int)bars.size())
    { // done sorting

        animationIsFinished = true;
        if (looping)
        {
            currentStep = 1;
            restoreList();
            update();
            shuffle();
            setBarColor(0, Qt::red);
            // run the animation on sort.
            QTimer::singleShot(1000, this, &StalinSortRenderer::runSortStep);
            return;
        }
        else
        {
            return;
        }
    }

    animationIsFinished = false;

    if (bars[currentStep].val < bars[currentStep - 1].val)
    {
        // time to take current step bar out back
        bars.erase(bars.begin() + currentStep); // clear bar that is out of line.
        update();
        if (looping)
        {
            QTimer::singleShot(500, this, &StalinSortRenderer::runSortStep);
        }
        else
        { // this else is for human player vs ai, to make it "possible" to beat
            QTimer::singleShot(1500, this, &StalinSortRenderer::runSortStep);
        }

        return;
    }
    else
    {
        setBarColor(currentStep, Qt::red); // set bar to red to show we've looked at it.
        currentStep++;
        update();

        if (looping)
        {
            QTimer::singleShot(500, this, &StalinSortRenderer::runSortStep);
        }
        else
        { // this else is for human player vs ai, to make it "possible" to beat
            QTimer::singleShot(1500, this, &StalinSortRenderer::runSortStep);
        }

        return;
    }
}
