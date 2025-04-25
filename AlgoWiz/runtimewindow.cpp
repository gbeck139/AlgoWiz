/**
 * @file runtimewindow.cpp
 * @brief Implementation of the RuntimeWindow class, which renders runtime complexity visuals (e.g., Big-O growth curves) for algorithm education modules.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#include "runtimewindow.h"
#include <QLabel>
#include <QPainter>

RuntimeWindow::RuntimeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Runtime");
    resize(400, 300);
}

void RuntimeWindow::paintEvent(QPaintEvent *evt)
{
    QWidget::paintEvent(evt);

    QPainter p(this);

    // Draw the runtime complexity image just below the banner area
    QPixmap img(":/images/runtime.jpg");
    if (!img.isNull()) {
        int margin = 16;
        int bannerBottom = 18; // Space for the banner or top padding
        int x = margin;
        int y = bannerBottom + margin;
        int w = width() - margin*2;

        QPixmap scaled = img.scaledToWidth(w, Qt::SmoothTransformation);
        p.drawPixmap(x, y, scaled);
    }
}
