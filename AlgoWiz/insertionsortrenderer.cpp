#include "insertionsortrenderer.h"
#include <QDebug>
#include <QTimer>

InsertionSortRenderer::InsertionSortRenderer()
{
    startAnimation();
}

void InsertionSortRenderer::runSortStep()
{
    // case: done sorting
    animationIsFinished = false;
    if (currentStep >= (int) bars.size()) {
        stepInProgress = false;
        animationIsFinished = true; // true because at this point the animation is in the sorted state
        if (looping) {
            currentStep = 1;
            whileStep = 0;
            update();
            shuffle();
            // run the animation on sort.
            QTimer::singleShot(
                2000,
                this,
                &InsertionSortRenderer::runSortStep); // pause for 2 sec before running the sort again
            return;
        } else {
            return;
        }
    }

    // new outer loop iteration is occuring
    if (!stepInProgress) {
        // bar color change
        whileStep = currentStep;
        stepInProgress = true;
        setBarColor(currentStep, Qt::red);
        update();
        QTimer::singleShot(2000, this, &InsertionSortRenderer::runSortStep);
        return;
    }

    // case: bar needs to move left (we need to do a swap)
    if (whileStep > 0 && bars[whileStep - 1].val > bars[whileStep].val) {
        std::swap(bars[whileStep - 1], bars[whileStep]);
        whileStep--;
        update();
        QTimer::singleShot(2000, this, &InsertionSortRenderer::runSortStep);
        return;

    } else { // case: bar is where it's supposed to be
        setBarColor(whileStep, defaultColor);
        setBarColor(currentStep, defaultColor);
        stepInProgress = false;
        currentStep++;
        update();
        QTimer::singleShot(200, this, &InsertionSortRenderer::runSortStep);
    }
}

void InsertionSortRenderer::startAnimation()
{
    shuffle();
    update();
    runSortStep();
}
