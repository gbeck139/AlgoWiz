/**
 * @file BFSWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the BFSWindow class, which represents the BFS algorithm visualization window.
 * @date 2025-04-25
 */

#ifndef BFSWINDOW_H
#define BFSWINDOW_H

#include <QWidget>

/**
 * @class BFSWindow
 * @brief BFSWindow class provides a QWidget-based window for visualizing Breadth-First Search (BFS).
 */
class BFSWindow : public QWidget
{
public:
    /**
     * @brief Constructor for BFSWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    BFSWindow(QWidget *parent = nullptr);
};

#endif // BFSWINDOW_H
