#ifndef LESSONWINDOW_H
#define LESSONWINDOW_H

#include <QWidget>
#include <QPixmap>

class QLabel;
class QPushButton;
class QPaintEvent;
class QResizeEvent;

class LessonWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LessonWindow(QWidget    *algoWidget,
                          const QString &wizardPng,
                          QWidget    *parent = nullptr);

    // Module‑specific text goes here:
    void setBannerText(const QString &text);

protected:
    void paintEvent(QPaintEvent   *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget     *contentPane;
    QLabel      *textBanner;
    QPushButton *exitBtn;
    QPixmap      wizardFull;
};

#endif // LESSONWINDOW_H
