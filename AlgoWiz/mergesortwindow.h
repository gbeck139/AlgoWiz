/**
 * @file mergesortwindow.h
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the declaration of the MergeSortWindow class to create the window for mergesort.
 * @date 2025-04-24
 */

#ifndef MERGESORTWINDOW_H
#define MERGESORTWINDOW_H

#include <QWidget>
#include "mergesortrenderer.h"

class MergeSortWindow : public QWidget
{
public:
    /**
     * @brief MergeSortWindow - constructs a MergeSortWindow
     * @param parent The parent widget
     */
    MergeSortWindow(QWidget *parent = nullptr);

private:
    /**
     * @brief renderer - the mergeSortRenderer to display the merge sort animation and starts it automatically.
     */
    mergeSortRenderer *renderer;
};

#endif // MERGESORTWINDOW_H
