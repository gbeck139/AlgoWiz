#include "sortingalgorenderer.h"
#include <algorithm>
#include <random>

sortingAlgoRenderer::sortingAlgoRenderer()
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

sortingAlgoRenderer::sortingAlgoRenderer(std::vector<int> vec)
{
    largestBar = 0;

    for (int i : vec) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        if (i > largestBar) {
            largestBar = i;
        }

        bars.push_back(b);
    }

    startAnimation();
}

void sortingAlgoRenderer::shuffle()
{
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(bars), std::end(bars), rng);
}

void sortingAlgoRenderer::displayBars()
{
    //
}

void sortingAlgoRenderer::setBarColor(int idx, QColor color)
{
    // set the bar at idx to color
    if (bars.size() > idx && idx >= 0) {
        bars[idx].color = color;
    }
}

// helper: display bars, start a QTimer
void sortingAlgoRenderer::startAnimation()
{
    //
}
