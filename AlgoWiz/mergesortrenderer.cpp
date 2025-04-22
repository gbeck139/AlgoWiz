#include "mergesortrenderer.h"
#include <QTimer>

mergeSortRenderer::mergeSortRenderer()
{
    for (int i = 21; i <= 32; i++) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 32; // hardcoded to our loop

    startAnimation();
}

void mergeSortRenderer::startAnimation()
{
    shuffle();
    for (int i = 0; i < (int) bars.size(); i++) {
        setBarColor(i, defaultColor);
    }
    mergeQueue = std::queue<std::function<void()>>();
    queueMergeSteps(0, bars.size() - 1);
    runNextStep();
}

void mergeSortRenderer::queueMergeSteps(int left, int right)
{
    // base case
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    queueMergeSteps(left, mid);
    queueMergeSteps(mid + 1, right);

    // now we add to function queue
    mergeQueue.push([=]() { merge(left, mid, right); });
}
void mergeSortRenderer::merge(int left, int mid, int right)
{
    // compare each element with the adjacent list to sort and merge the two adjacent lists
    std::vector<bar> merged;

    setBarColor(mid, Qt::cyan);

    update();

    // Perform the merge operation
    int i = left;
    int j = mid + 1;

    // standard case, elements on both sides of the list we're merging
    while (i <= mid && j <= right) {
        if (bars[i].val <= bars[j].val) {
            merged.push_back(bars[i++]);
        } else {
            merged.push_back(bars[j++]);
        }
    }

    while (i <= mid) {
        merged.push_back(bars[i++]);
    }

    while (j <= right) {
        merged.push_back(bars[j++]);
    }

    for (int k = 0; k < (int) merged.size(); ++k) {
        bars[left + k] = merged[k];
        setBarColor(left + k, Qt::cyan);
    }

    update();

    int delay = 1200;
    if (looping) { // handle regular animation and sorting game
        delay = 500;
    }

    // reset colors and continue to next step after a delay
    QTimer::singleShot(delay, this, [=]() {
        // reset colors
        setBarColor(left, defaultColor);
        setBarColor(mid, defaultColor);
        setBarColor(right, defaultColor);

        // reset merged section colors
        for (int k = 0; k < (int) merged.size(); ++k) {
            setBarColor(left + k, defaultColor);
        }
        
        update();
        
        // Continue to next step
        QTimer::singleShot(200, this, &mergeSortRenderer::runNextStep);
    });
}
void mergeSortRenderer::runNextStep()
{
    if (mergeQueue.empty()) {
        animationIsFinished = true;

        if (looping) {
            QTimer::singleShot(500, this, [=]() {
                animationIsFinished = false;
                startAnimation();
            });
            return;
        } else {
            return;
        }
    }

    // pop and animate?
    auto nextStep = mergeQueue.front();
    mergeQueue.pop();

    nextStep(); // this will be a call to merge()
}
