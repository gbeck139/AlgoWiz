#include "sortinggamewindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "insertionsortrenderer.h"
#include "mergesortrenderer.h"
#include "stalinsortrenderer.h"

SortingGameWindow::SortingGameWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Sorting Game");
    resize(400, 300);
    layout = new QVBoxLayout();

    connect(this,
            &SortingGameWindow::difficultySelected,
            this,
            &SortingGameWindow::handleDifficultySelection);

    QHBoxLayout *buttonBox = new QHBoxLayout();

    easySelection = new QPushButton("Easy mode", parent);
    mediumSelection = new QPushButton("Normal mode", parent);
    hardSelection = new QPushButton("Hard mode", parent);

    buttonBox->addWidget(easySelection);
    buttonBox->addWidget(mediumSelection);
    buttonBox->addWidget(hardSelection);

    layout->addLayout(buttonBox);

    connect(easySelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(0); });
    connect(mediumSelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(1); });
    connect(hardSelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(2); });

    playerController = new sortingGamePlayer(this);

    aiPlayer = new InsertionSortRenderer(); // set to easy mode by default
    aiPlayer->setLooping(false);

    layout->addWidget(aiPlayer);

    setLayout(layout);
}

void SortingGameWindow::handleDifficultySelection(int difficulty)
{
    delete aiPlayer; // clear out previous difficulty selection
    if (difficulty == 0)
    {
        aiPlayer = new InsertionSortRenderer();
    }
    else if (difficulty == 1)
    {
        aiPlayer = new mergeSortRenderer();
    }
    else
    {
        aiPlayer = new StalinSortRenderer();
    }

    aiPlayer->setLooping(false);
    layout->addWidget(aiPlayer);
}
