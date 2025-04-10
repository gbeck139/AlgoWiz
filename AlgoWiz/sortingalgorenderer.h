#ifndef SORTINGALGORENDERER_H
#define SORTINGALGORENDERER_H

#include <QWidget>

class sortingAlgoRenderer
{
public:
    sortingAlgoRenderer();
    sortingAlgoRenderer(std::vector<int> vec);

private:
    struct bar
    {
        int val;
        QColor color;
    };

    const QRgb orange = 0xff8c00;
    QColor defaultColor = QColor(orange);

    std::vector<bar> bars;

    int largestBar;

    void shuffle();

    void displayBars();

    void setBarColor(int idx, QColor color);

    void startAnimation();

    // virtual void sort(); // sort is obviously implemented by child classes <sort type>
};

#endif // SORTINGALGORENDERER_H
