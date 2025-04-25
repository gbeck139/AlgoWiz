/**
 * @file RuntimeWindow.h
 * @brief Header file for the RuntimeWindow class, which provides a visualization window for algorithm runtime complexity concepts (Big-O notation curves, etc.).
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#ifndef RUNTIMEWINDOW_H
#define RUNTIMEWINDOW_H

#include <QWidget>

/**
 * @class RuntimeWindow
 * @brief RuntimeWindow class provides a QWidget-based window for visualizing runtime complexity concepts such as Big-O growth curves.
 */
class RuntimeWindow : public QWidget
{
public:
    /**
     * @brief Constructor for RuntimeWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    RuntimeWindow(QWidget *parent = nullptr);

    /**
     * @brief Handles the custom painting of runtime complexity visuals (e.g., Big-O growth curves).
     * @param evt - the paint event.
     */
    void paintEvent(QPaintEvent *evt);
};

#endif // RUNTIMEWINDOW_H
