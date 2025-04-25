/**
 * @file MainWindow.h
 * @brief Header file for the MainWindow class, which serves as the main application window managing navigation between algorithm visualizations and tracking progress.
 * @author Jared Pratt, Grant Beck, Isaac Huntsman, Joshua Eggett, Woojin Lee, David Perry
 * @date 2025-04-25
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "qpushbutton.h"
#include <QMainWindow>
#include <dfswindow.h>
#include <runtimewindow.h>
#include <QVector>
#include <QLabel>
#include <QGuiApplication> // for automatic resizing of window
#include <QScreen>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief MainWindow class provides the central user interface for the application, managing navigation between algorithm windows and displaying progress.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Handles the custom painting of the main window background.
     * @param event - the paint event.
     */
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    /**
     * @brief Sets the style for QPushButton widgets (e.g., colors, fonts).
     * @param btn - the QPushButton to style.
     */
    void setStyle(QPushButton* btn);

    /**
     * @brief Adjusts the size of a child window relative to the screen size.
     * @param window - the window to adjust.
     * @param newWidth - the calculated width (output parameter).
     * @param newHeight - the calculated height (output parameter).
     */
    void adjustWindowSize(QWidget* window, int &newWidth, int &newHeight);

    int totalTasks = 0;
    int completed = 0;
    QVector<bool> seen;
    QLabel *progressPercentLabel;
};

#endif // MAINWINDOW_H
