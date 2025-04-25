/**
 * @file binarysearchwindow.h
 * @author Woojin Lee, David Perry
 * @brief This file contains the declaration of the BinarySearchWindow class to create the window for binarysearch algorithm.
 * @date 2025-04-24
 */

#ifndef BINARYSEARCHWINDOW_H
#define BINARYSEARCHWINDOW_H

#include <QWidget>
#include "binarysearchrenderer.h"

class BinarySearchWindow : public QWidget
{
public:
    /**
     * @brief BinarySearchWindow - constructs a BinarySearchWindow
     * @param parent The parent widget
     */
    BinarySearchWindow(QWidget *parent = nullptr);

private:
    /**
     * @brief renderer - the BinarySearchRenderer to display the binary search animation and starts it automatically.
     */
    BinarySearchRenderer *renderer;
};

#endif // BINARYSEARCHWINDOW_H
