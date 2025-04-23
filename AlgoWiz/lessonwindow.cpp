#include "lessonwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

LessonWindow::LessonWindow(QWidget    *algoWidget,
                           const QString &wizardPng,
                           QWidget    *parent)
    : QWidget(parent),
    contentPane(new QWidget(this)),
    textBanner(new QLabel("", this)),
    exitBtn(new QPushButton("✕", this)),
    wizardFull(wizardPng)
{
    //Frameless & maximized (fills current Space / OS screen)
    setWindowFlags(Qt::FramelessWindowHint);
    showMaximized();

    //Red exit button, always in top‑right
    exitBtn->setFixedSize(40, 40);
    exitBtn->setStyleSheet(R"(
        QPushButton {
            background: #d30000;
            color: white;
            border: none;
            border-radius: 20px;
            font: 700 22px "Arial";
        }
        QPushButton:hover {
            background: #900000;
        }
    )");
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);

    //Banner styling + wrap + horizontal expand
    textBanner->setStyleSheet(R"(
        background: rgba(0,0,0,0.75);
        color: white;
        font: 600 18px "Arial";
        padding: 12px;
        border-radius: 8px;
    )");
    textBanner->setWordWrap(true);
    textBanner->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Fixed
        );

    auto *v = new QVBoxLayout(contentPane);
    // bump right margin so the banner never slides under the ✕
    v->setContentsMargins(48, 48, 200, 70);
    v->setSpacing(12);
    v->addWidget(textBanner,0);
    v->addWidget(algoWidget,1);

    //Root layout: invisible 1/3 + contentPane (2/3)
    auto *root = new QHBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);
    root->addStretch(1);
    root->addWidget(contentPane, 2);
}

void LessonWindow::setBannerText(const QString &text)
{
    textBanner->setText(text);
}

void LessonWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if (!wizardFull.isNull()) {
        QPainter p(this);
        p.drawPixmap(
            rect(),
            wizardFull.scaled(
                size(),
                Qt::KeepAspectRatioByExpanding,
                Qt::SmoothTransformation
                )
            );
    }
}

void LessonWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // keep the red ✕ flush to the corner
    exitBtn->move(width() - exitBtn->width() - 16, 16);
}
