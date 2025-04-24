/**
 * @file stalinsortwindow.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the Stalin sort window class.
 * @date 2025-04-24
 */

#ifndef STALINSORTWINDOW_H
#define STALINSORTWINDOW_H
#include <QWidget>
#include "stalinsortrenderer.h"

/**
 * @brief The StalinSortWindow class is a class that extends QWidget.
 * Used to display the Stalin sort animation.
 */
class StalinSortWindow : public QWidget
{
public:
    /**
     * @brief StalinSortWindow constructor
     * @param parent The parent widget
     */
    StalinSortWindow(QWidget *parent = nullptr);
    /**
     * @brief The renderer for the Stalin sort animation
     */
    StalinSortRenderer *renderer;
};

#endif // STALINSORTWINDOW_H
