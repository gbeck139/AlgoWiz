/**
 * @file GraphTheoryWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the GraphTheoryWindow class, which represents the graph theory visualization window.
 * @date 2025-04-25
 */


#ifndef GRAPHTHEORYWINDOW_H
#define GRAPHTHEORYWINDOW_H

#include <QWidget>

/**
 * @class GraphTheoryWindow
 * @brief GraphTheoryWindow class provides a QWidget-based window for visualizing graph theory concepts.
 */
class GraphTheoryWindow : public QWidget
{
public:
    /**
     * @brief Constructor for GraphTheoryWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    GraphTheoryWindow(QWidget *parent = nullptr);
};

#endif // GRAPHTHEORYWINDOW_H
