/**
 * @file insertionsortwindow.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the insertion sort window class.
 * @date 2025-04-24
 */

#ifndef INSERTIONSORTWINDOW_H
#define INSERTIONSORTWINDOW_H

#include <QWidget>

#include "insertionsortrenderer.h"

/**
 * @brief The InsertionSortWindow class is a class that extends QWidget.
 * Used to display the insertion sort animation.
 */
class InsertionSortWindow : public QWidget
{
public:
    /**
     * @brief InsertionSortWindow constructor
     * @param parent The parent widget
     */
    InsertionSortWindow(QWidget *parent = nullptr);

private:
    /**
     * @brief The renderer for the insertion sort animation
     */
    InsertionSortRenderer *renderer;
};

#endif // INSERTIONSORTWINDOW_H
