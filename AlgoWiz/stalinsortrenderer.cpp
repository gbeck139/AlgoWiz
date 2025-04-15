#include "stalinsortrenderer.h"
#include <QTimer>

StalinSortRenderer::StalinSortRenderer() {
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

void StalinSortRenderer::restoreList() {
    bars.clear();

    for (int i = 1; i <= 20; i++) {
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
    update();
    runSortStep();
}

void StalinSortRenderer::runSortStep() {
    // done sorting
    if (currentStep >= (int) bars.size()) {
        currentStep = 0;
        restoreList();
        update();
        shuffle();
        // run the animation on sort.
        QTimer::singleShot(
            2000,
            this,
            &StalinSortRenderer::runSortStep); // pause for 2 sec before running the sort again
        return;
    }

    if(bars[currentStep].val < bars[currentStep - 1].val) {
        // time to take current step bar out back
        bars.erase(bars.begin() + currentStep); // clear bar that is out of line.
        update();
        QTimer::singleShot(
            200,
            this,
            &StalinSortRenderer::runSortStep); // continue on without incrementing current step since we decreased size of vector.
        return;
    }
    else {
        setBarColor(currentStep, Qt::red); // set bar to red to show we've looked at it.
        currentStep++;
        update();
        QTimer::singleShot(
            200,
            this,
            &StalinSortRenderer::runSortStep);
        return;
    }
}
