/**
 * @file main.cpp
 * @brief Entry point of the AlgoWiz educational app. Initializes the application and displays the main window interface.
 * @date 2025-04-25
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
