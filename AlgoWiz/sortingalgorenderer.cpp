#include "sortingalgorenderer.h"
#include <algorithm>
#include <random>
#include <QPainter>

sortingAlgoRenderer::sortingAlgoRenderer(QWidget* parent): QWidget(parent)
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
    update();
}

void sortingAlgoRenderer::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int widgetWidth = width();
    int widgetHeight = height();

    int numBars = static_cast<int>(bars.size());
    if (numBars == 0 || largestBar == 0) return;

    double barWidth = static_cast<double>(widgetWidth) / numBars;

    for (int i = 0; i < numBars; ++i) { // draw the bars
        const bar& bar = bars[i];

        double normalizedHeight = static_cast<double>(bar.val) / largestBar;
        int barHeightPx = static_cast<int>(normalizedHeight * widgetHeight);

        int x = static_cast<int>(i * barWidth);
        int y = widgetHeight - barHeightPx;

        QRectF rect(x, y, barWidth, barHeightPx);

        painter.setBrush(bar.color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }
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
    // run sort function, which sets up qtimer singleshots for each step then qtimer singleshot for recalling start animation.
}
