/**
 * @file sortingalgorenderer.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the sortingAlgoRenderer class and the bar struct used in the sorting algorithm renderers.
 * @date 2025-04-24
 */

#ifndef SORTINGALGORENDERER_H
#define SORTINGALGORENDERER_H

#include <QWidget>

class sortingAlgoRenderer : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief constructs a sortingAlgoRenderer. Initializes bars with a set of 20 bars (1-20 values)
     * @param parent - a parent widget for displaying this widget in.
     */
    explicit sortingAlgoRenderer(QWidget *parent = nullptr);

    /**
     * @brief constructor that sets whether the animation should loop as well.
     * @param parent - a parent widget for displaying this widget in.
     */
    sortingAlgoRenderer(QWidget *parent, bool looping);

    /**
     * @brief sets whether to loop the animation or not
     * @param loops - boolean to set whether to loop or not.
     */
    void setLooping(bool loops);

    /**
     * @brief getter for animationIsFinished, true if the animation is in the 'finished' state where it is sorted.
     * @return bool whether the animation is finished
     */
    bool isAnimationFinished();

protected:
    /**
     * @brief bar - struct defining a bar, containing value (height) and color to display as.
     */
    struct bar
    {
        int val;
        QColor color;
    };

    /**
     * @brief orange - an orangey color thats used for the default color of the bars.
     */
    const QRgb orange = 0xff8c00;

    /**
     * @brief defaultColor - uses orange color to create a QColor for the default.
     */
    QColor defaultColor = QColor(orange);

    /**
     * @brief bars - vector of bars to display / sort with.
     */
    std::vector<bar> bars;

    /**
     * @brief looping - boolean whether to loop the animation
     */
    bool looping = true;

    /**
     * @brief animationIsFinished - whether the animation is currently in the finished sorting state.
     */
    bool animationIsFinished = false;

    /**
    * @brief largestBar - integer that tracks the largest value in the bars vector for calculating display height of bars.
    */
    int largestBar;

    /**
    * @brief shuffles the list of bars to a random order.
    */
    void shuffle();

    /**
    * @brief sets the color of a bar in the list.
    * @param idx The index of the bar to set the color of.
    * @param color The color to set the bar to.
    */
    void setBarColor(int idx, QColor color);


    /**
    * @brief Draws the bars in the vector with their color.
    * @param *event the QPaintEvent occuring.
    */
    void paintEvent(QPaintEvent *event) override;


};

#endif // SORTINGALGORENDERER_H
