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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    // Set style for buttons
    void setStyle(QPushButton* btn);
    void adjustWindowSize(QWidget* window, int &newWidth, int &newHeight);

    int totalTasks = 0;
    int completed = 0;
    QVector<bool> seen;
    QLabel *progressPercentLabel;

public slots:


};
#endif // MAINWINDOW_H
