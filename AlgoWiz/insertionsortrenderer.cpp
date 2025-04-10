#include "insertionsortrenderer.h"

Insertionsortrenderer::Insertionsortrenderer() {
    // put 20 bar structs in the bars vector
    for (int i = 1; i <= 20; i++) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 20; // hardcoded to our loop

    sort(); // start the sort animation loop
}

void Insertionsortrenderer::sort() {
    // implement insertion sort here, with qtimer steps to call displayBars from the sortingalgorenderer.

    for (ulong step = 1; step < bars.size(); step++) { // probably need to change this so that we step once per function call of a helper so that the steps are queued up but not processed until time to render
        auto bar = bars[step];
        bar.color = QColor::fromRgb(255, 0, 0, 255); // set selected bar to red to show its being sorted.
        int j = step - 1;

        while (j >=0 && bar.val < bars[j].val) {
            bars[j + 1] = bars[j];
            --j;
        }
        bars[j + 1] = bar;
    }
}
