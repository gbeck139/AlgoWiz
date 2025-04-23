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

        //draw the runtime image just under the banner
        QPixmap img(":/images/runtime.jpg");
        if (!img.isNull()) {
            int margin = 16;
            int bannerBottom = 18;
            int x = margin;
            int y = bannerBottom + margin;
            int w = width() - margin*2;

            QPixmap scaled = img.scaledToWidth(w, Qt::SmoothTransformation);
            p.drawPixmap(x, y, scaled);
        }
    }
