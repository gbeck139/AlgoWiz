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
    resize(800, 800);
    layout = new QVBoxLayout();

    // signal from here to

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
    connect(playerController, &sortingGamePlayer::playerFinished, this, &SortingGameWindow::handlePlayerFinished);

    aiPlayer = new InsertionSortRenderer(); // set to easy mode by default
    aiPlayer->setLooping(false);

    QLabel *aiLabel = new QLabel("AI Player");
    QLabel *playerLabel = new QLabel("Sort the bars below! Beat the sorting algorithm!");

    QFont labelFont = aiLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(12);
    aiLabel->setFont(labelFont);
    playerLabel->setFont(labelFont);

    aiLabel->setAlignment(Qt::AlignCenter);
    playerLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(aiLabel);
    layout->addWidget(aiPlayer);
    layout->addWidget(playerLabel);
    layout->addWidget(playerController);

    gameResultLabel = new QLabel("");
    gameResultLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(gameResultLabel);

    setLayout(layout);
}

void SortingGameWindow::handleDifficultySelection(int difficulty)
{
    // Clear previous result
    gameResultLabel->setText("");

    // Remove the old AI player widget
    if (aiPlayer)
    {
        layout->removeWidget(aiPlayer);
        delete aiPlayer;
    }

    // Create the new AI player based on difficulty
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

    // Insert the AI player at index 2 (after the buttons and AI label)
    layout->insertWidget(2, aiPlayer);

    // check every 100ms if AI won to handle displaying message
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SortingGameWindow::checkAIProgress);

    timer->start(100); // Check every 100ms

    playerController->resetGame();
}

void SortingGameWindow::checkAIProgress()
{
    if (aiPlayer && aiPlayer->isAnimationFinished())
    {
        // AI has finished sorting
        if (!aiFinished)
        {
            aiFinished = true;
            // Check if player also finished
            if (!playerFinished) {
                gameResultLabel->setText("AI won the race!");
            }
        }

        // Disconnect the timer
        QTimer *timer = qobject_cast<QTimer *>(sender());
        if (timer)
        {
            timer->stop();
            timer->deleteLater();
        }
    }
}

void SortingGameWindow::handlePlayerFinished()
{
    playerFinished = true;
    qDebug() << "Playerfinished is true, ai finished is:" << aiFinished;

    if (aiFinished)
    {
        gameResultLabel->setText("You lost");
    }
    else
    {
        gameResultLabel->setText("You won the race!");
    }
}
