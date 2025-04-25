/**
 * @file DijkstraWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the DijkstraWindow class, which represents the Dijkstra's algorithm visualization window.
 * @date 2025-04-25
 */

#ifndef DIJKSTRAWINDOW_H
#define DIJKSTRAWINDOW_H

#include <QWidget>

/**
 * @class DijkstraWindow
 * @brief DijkstraWindow class provides a QWidget-based window for visualizing Dijkstra's shortest path algorithm.
 */
class DijkstraWindow : public QWidget
{
public:
    /**
     * @brief Constructor for DijkstraWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    DijkstraWindow(QWidget *parent = nullptr);
};

#endif // DIJKSTRAWINDOW_H
