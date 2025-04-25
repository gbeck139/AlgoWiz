/**
 * @file DFSWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the DFSWindow class, which represents the DFS algorithm visualization window.
 * @date 2025-04-25
 */

#ifndef DFSWINDOW_H
#define DFSWINDOW_H

#include <QWidget>

/**
 * @class DFSWindow
 * @brief DFSWindow class provides a QWidget-based window for visualizing Depth-First Search (DFS).
 */
class DFSWindow : public QWidget
{
public:
    /**
     * @brief Constructor for DFSWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    DFSWindow(QWidget *parent = nullptr);
};

#endif // DFSWINDOW_H
