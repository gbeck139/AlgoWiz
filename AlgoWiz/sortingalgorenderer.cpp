#include "sortingalgorenderer.h"
#include <algorithm>
#include <random>
#include <QPainter>

sortingAlgoRenderer::sortingAlgoRenderer(QWidget *parent) : QWidget(parent)
{
    // put 20 bar structs in the bars vector
    for (int i = 1; i <= 20; i++)
    {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 20; // hardcoded to our loop
}

sortingAlgoRenderer::sortingAlgoRenderer(QWidget *parent, bool looping)
    : QWidget(parent)
{
    this->looping = looping;
    // put 20 bar structs in the bars vector
    for (int i = 1; i <= 20; i++) {
        bar b;
        b.val = i;
        b.color = defaultColor;

        bars.push_back(b);
    }

    largestBar = 20; // hardcoded to our loop
}

void sortingAlgoRenderer::shuffle()
{
    std::random_device rd;
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(bars), std::end(bars), rng);
}

void sortingAlgoRenderer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int widgetWidth = width();
    int widgetHeight = height();

    int numBars = static_cast<int>(bars.size());
    if (numBars == 0 || largestBar == 0)
        return;

    double barWidth = static_cast<double>(widgetWidth) / numBars;

    for (int i = 0; i < numBars; ++i)
    { // draw the bars
        const bar &bar = bars[i];

        double normalizedHeight = static_cast<double>(bar.val) / largestBar;
        int barHeightPx = static_cast<int>(normalizedHeight * widgetHeight);

        int x = i * barWidth;
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
    if ((int) bars.size() > idx && idx >= 0) {
        bars[idx].color = color;
    }
}

bool sortingAlgoRenderer::isAnimationFinished()
{
    return animationIsFinished;
}
