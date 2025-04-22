#ifndef SORTINGGAMEWINDOW_H
#define SORTINGGAMEWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "sortingalgorenderer.h"
#include "sortinggameplayer.h"

class SortingGameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SortingGameWindow(QWidget *parent = nullptr);

private:
    QPushButton *easySelection;
    QPushButton *mediumSelection;
    QPushButton *hardSelection;
    QVBoxLayout *layout;
    sortingGamePlayer *playerController;
    sortingAlgoRenderer *aiPlayer;
public slots:
    void handleDifficultySelection(int difficulty);

signals:
    void difficultySelected(int difficulty);
};

#endif // SORTINGGAMEWINDOW_H
