#ifndef SORTINGGAMEWINDOW_H
#define SORTINGGAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "sortingalgorenderer.h"
#include "sortinggameplayer.h"

class SortingGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SortingGameWindow(QWidget *parent = nullptr);

signals:
    void difficultySelected(int difficulty);

private slots:
    void handleDifficultySelection(int difficulty);
    void checkAIProgress();
    void handlePlayerFinished();

private:
    QVBoxLayout *layout;
    QPushButton *easySelection;
    QPushButton *mediumSelection;
    QPushButton *hardSelection;
    sortingAlgoRenderer *aiPlayer;
    sortingGamePlayer *playerController;
    QLabel *gameResultLabel;
    bool aiFinished = false;
    bool playerFinished = false;
};

#endif // SORTINGGAMEWINDOW_H
