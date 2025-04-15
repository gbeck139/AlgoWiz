#include "insertionsortrenderer.h"
#include <QDebug>

InsertionSortRenderer::InsertionSortRenderer()
{
    // put 20 bar structs in the bars vector
    for (int i = 1; i <= 20; i++) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 20; // hardcoded to our loop

    startAnimation();
}

// the vector is sorted very quickly, and we want to watch it happen slowly
// the vector internals are changed extremely quickly, can't sync the view with our vector...

void InsertionSortRenderer::runSortStep()
{
    // case: done sorting
    if (currentStep >= (int) bars.size()) {
        stepInProgress = false;
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
    }

    // new outer loop iteration is occuring
    if (!stepInProgress) {
        // bar color change
        whileStep = currentStep;
        stepInProgress = true;
        setBarColor(currentStep, Qt::red);
        update();
        QTimer::singleShot(200, this, &InsertionSortRenderer::runSortStep);
        return;
    }

    // case: bar needs to move left (we need to do a swap)
    if (whileStep > 0 && bars[whileStep - 1].val > bars[whileStep].val) {
        std::swap(bars[whileStep - 1], bars[whileStep]);
        whileStep--;
        update();
        QTimer::singleShot(200, this, &InsertionSortRenderer::runSortStep);
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
