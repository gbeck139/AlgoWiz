/**
 * @file lessonwindow.cpp
 * @brief Implementation of the LessonWindow class, providing a styled window for lessons with optional banner text and background decoration.
 * @author Jared Pratt, Grant Beck
 * @date 2025-04-25
 */

#include "lessonwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

LessonWindow::LessonWindow(QWidget *algoWidget,
                           const QString &wizardPng,
                           bool showBanner,
                           QWidget *parent)
    : QWidget(parent),
    contentPane(new QWidget(this)),
    textBanner(new QLabel("", this)),
    exitBtn(new QPushButton("✕", this)),
    wizardFull(wizardPng)
{
    // Frameless and maximized window (fills the current screen)
    setWindowFlags(Qt::FramelessWindowHint);
    showMaximized();

    // Red exit button, positioned in the top-right corner
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

    // Styling for the banner text
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

    // Layout for the content pane
    auto *v = new QVBoxLayout(contentPane);
    if (showBanner)
    {
        // Extra right margin to prevent banner overlap with the ✕ button
        v->setContentsMargins(48, 48, 200, 70);
        v->setSpacing(12);
        v->addWidget(textBanner,0);
        v->addWidget(algoWidget,1);
    } else {
        v-> setContentsMargins(48, 16, 16, 16);
        v->setSpacing(0);
        textBanner->hide();
    }
    v->addWidget(algoWidget, 1);

    // Root layout: invisible left spacer (1/3) + content pane (2/3)
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
    // Keep the exit button flush with the top-right corner on resize
    exitBtn->move(width() - exitBtn->width() - 16, 16);
}
