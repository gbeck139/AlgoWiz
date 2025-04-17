#include "binarysearchrenderer.h"
#include <QDebug>
#include <QTimer>

BinarySearchRenderer::BinarySearchRenderer()
{
    startAnimation();
}

void BinarySearchRenderer::runSearchStep()
{
    //Set initial value
    if (!stepInProgress) {
        low = 0;
        high = bars.size() - 1;
        stepInProgress = true;
        target = 14;
        update();
        QTimer::singleShot(1000, this, &BinarySearchRenderer::runSearchStep);
        return;
    }

    //When the target is not found(if it failed)
    if (low > high) {
        for (int i = 0; i < (int) bars.size(); ++i)
            setBarColor(i, Qt::gray);
        update();
        return;
    }

    int mid = (low + high) / 2;

    //Move the position, and show it
    for (int i = 0; i < (int) bars.size(); ++i) {
        if (i == mid)
            setBarColor(i, Qt::red); //Current position
        else if (i >= low && i <= high)
            setBarColor(i, defaultColor); //Set yellow color in valid side
        else
            setBarColor(i, Qt::gray); //Block the opposite side
    }

    update();

    //Change the value
    if (bars[mid].val == target) {
        setBarColor(mid, Qt::green);
        update();
        stepInProgress = false;
        QTimer::singleShot(1000, this, &BinarySearchRenderer::runSearchStep);
        return;
    } else if (bars[mid].val < target) {
        low = mid + 1;
    } else {
        high = mid - 1;
    }

    QTimer::singleShot(1000, this, &BinarySearchRenderer::runSearchStep);
}

void BinarySearchRenderer::startAnimation()
{
    update();
    runSearchStep();
}
