#ifndef SORTINGALGORENDERER_H
#define SORTINGALGORENDERER_H

#include <QWidget>


class sortingAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    explicit sortingAlgoRenderer(QWidget* parent = nullptr);
    sortingAlgoRenderer(std::vector<int> vec);

protected:
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

    void paintEvent(QPaintEvent* event) override;

};

#endif // SORTINGALGORENDERER_H
