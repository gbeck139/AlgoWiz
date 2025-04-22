#include "stalinsortrenderer.h"
#include <QTimer>

StalinSortRenderer::StalinSortRenderer() {
    startAnimation();
}

void StalinSortRenderer::restoreList() {
    bars = std::vector<bar>();

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
    setBarColor(0, Qt::red);
    update();
    runSortStep();
}

void StalinSortRenderer::runSortStep() {
    if (currentStep >= (int) bars.size()) { // done sorting

        animationIsFinished = true;
        if (looping) {
            currentStep = 1;
            restoreList();
            update();
            shuffle();
            setBarColor(0, Qt::red);
            // run the animation on sort.
            QTimer::singleShot(
                1000,
                this,
                &StalinSortRenderer::runSortStep); // pause for 2 sec before running the sort again
            return;
        }
    }

    animationIsFinished = false;

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
