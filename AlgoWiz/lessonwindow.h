/**
 * @file LessonWindow.h
 * @author Jared Pratt, Grant Beck
 * @brief Header file for the LessonWindow class, which provides a reusable window with optional banner text and wizard-themed decoration for educational modules.
 * @date 2025-04-25
 */

#ifndef LESSONWINDOW_H
#define LESSONWINDOW_H

#include <QWidget>
#include <QPixmap>

class QLabel;
class QPushButton;
class QPaintEvent;
class QResizeEvent;

/**
 * @class LessonWindow
 * @brief LessonWindow provides a styled QWidget with an optional banner, background image, and an embedded content pane for lesson modules.
 */
class LessonWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for LessonWindow.
     * @param algoWidget - the main content widget to display within the lesson window.
     * @param wizardPng - the path to the wizard PNG image used for decoration.
     * @param showBanner - flag to determine whether to show the top text banner (optional, defaults to true).
     * @param parent - the parent widget (optional, defaults to nullptr).
     */
    explicit LessonWindow(QWidget *algoWidget,
                         const QString &wizardPng,
                         bool showBanner = true,
                         QWidget *parent = nullptr);

    /**
     * @brief Sets the text displayed in the banner at the top of the window.
     * @param text - the text to display in the banner.
     */
    void setBannerText(const QString &text);

protected:
    /**
     * @brief Handles the custom painting of the window, including background and wizard image.
     * @param event - the paint event.
     */
    void paintEvent(QPaintEvent   *event) override;

    /**
     * @brief Handles resizing logic to adjust layout and background scaling.
     * @param event - the resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget     *contentPane;
    QLabel      *textBanner;
    QPushButton *exitBtn;
    QPixmap      wizardFull;
};

#endif // LESSONWINDOW_H
