#ifndef SORTINGALGORENDERER_H
#define SORTINGALGORENDERER_H

#include <QWidget>

class sortingAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    explicit sortingAlgoRenderer(QWidget *parent = nullptr);
    sortingAlgoRenderer(QWidget *parent, bool looping);
    bool isAnimationFinished();

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

    void setBarColor(int idx, QColor color);

    void paintEvent(QPaintEvent *event) override;

    bool looping = true;

    bool animationIsFinished = false;
};

#endif // SORTINGALGORENDERER_H
