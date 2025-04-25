/**
 * @file sortinggamewindow.cpp
 * @author Isaac Huntsman, Joshua Eggett
 * @brief This file contains the implementation for the SortingGameWindow which is used to create the sorting mini game.
 * @date 2025-04-24
 */

#include "sortinggamewindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include "insertionsortrenderer.h"
#include "mergesortrenderer.h"
#include "stalinsortrenderer.h"
#include "styleutils.h"

SortingGameWindow::SortingGameWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Sorting Game");
    resize(800, 800);
    layout = new QVBoxLayout(); // create the layout for the window.
    layout->addSpacing(50);

    // signal from here to
    connect(this,
            &SortingGameWindow::difficultySelected,
            this,
            &SortingGameWindow::handleDifficultySelection);

    QHBoxLayout *buttonBox = new QHBoxLayout();

    easySelection = new QPushButton("Easy mode", parent);
    mediumSelection = new QPushButton("Normal mode", parent);
    hardSelection = new QPushButton("Hard mode", parent); // construct the buttons to select difficulty

    easySelection->setStyleSheet(gameButtonStyle());
    mediumSelection->setStyleSheet(gameButtonStyle());
    hardSelection->setStyleSheet(gameButtonStyle());

    buttonBox->addWidget(easySelection); // add buttons to the button horizontal box layout
    buttonBox->addWidget(mediumSelection);
    buttonBox->addWidget(hardSelection);

    layout->addLayout(buttonBox);

    connect(easySelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(0); });
    connect(mediumSelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(1); });
    connect(hardSelection, &QPushButton::clicked, this, [=]()
            { emit difficultySelected(2); }); // connect the buttons to the difficulty handler to change difficulty

    // Create opaque background frames for AI and player sections
    auto *aiBackingFrame = new QFrame(this);
    aiBackingFrame->setFrameShape(QFrame::StyledPanel);
    aiBackingFrame->setStyleSheet("QFrame { background-color: rgba(40, 40, 50, 0.6); border-radius: 12px; }");
    aiBackingFrame->setMinimumHeight(250);

    auto *playerBackingFrame = new QFrame(this);
    playerBackingFrame->setFrameShape(QFrame::StyledPanel);
    playerBackingFrame->setStyleSheet("QFrame { background-color: rgba(40, 40, 50, 0.6); border-radius: 12px; }");
    playerBackingFrame->setMinimumHeight(250);

    playerController = new sortingGamePlayer(this);
    connect(playerController, &sortingGamePlayer::playerFinished, this, &SortingGameWindow::handlePlayerFinished);

    aiPlayer = new InsertionSortRenderer(); // set to easy mode by default
    aiPlayer->setLooping(false);

    QLabel *aiLabel = new QLabel("AI Player");
    QLabel *playerLabel = new QLabel("Sort the bars below! Beat the sorting algorithm!");

    QFont labelFont = aiLabel->font();
    labelFont.setBold(true);
    labelFont.setPointSize(25);
    aiLabel->setFont(labelFont);
    playerLabel->setFont(labelFont);

    aiLabel->setAlignment(Qt::AlignCenter);
    playerLabel->setAlignment(Qt::AlignCenter);

    // Set label text color to white to match graph game
    aiLabel->setStyleSheet("QLabel { color: white; }");
    playerLabel->setStyleSheet("QLabel { color: white; }");

    // Create layouts for the backing frames
    auto *aiFrameLayout = new QVBoxLayout(aiBackingFrame);
    aiFrameLayout->addWidget(aiLabel);
    aiFrameLayout->addWidget(aiPlayer);
    aiFrameLayout->setContentsMargins(20, 20, 20, 20);

    auto *playerFrameLayout = new QVBoxLayout(playerBackingFrame);
    playerFrameLayout->addWidget(playerLabel);
    playerFrameLayout->addWidget(playerController);
    playerFrameLayout->setContentsMargins(20, 20, 20, 20);

    // Add the frames to the main layout instead of individual widgets
    layout->addWidget(aiBackingFrame);
    layout->addWidget(playerBackingFrame);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 10, 20, 20);

    gameResultLabel = new QLabel("");

    QFont font = gameResultLabel->font();
    font.setPointSize(30);
    gameResultLabel->setFont(font);

    gameResultLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(gameResultLabel);

    setLayout(layout);
}

void SortingGameWindow::handleDifficultySelection(int difficulty)
{
    // Clear previous result
    gameResultLabel->setText("");

    // Remove the old AI player widget from its parent layout
    if (aiPlayer)
    {
        QLayout* parentLayout = aiPlayer->parentWidget()->layout();
        if (parentLayout) {
            parentLayout->removeWidget(aiPlayer);
        }
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

    // Find the aiBackingFrame and add the new aiPlayer to its layout
    QFrame* aiBackingFrame = findChild<QFrame*>();
    if (aiBackingFrame && aiBackingFrame->layout()) {
        QVBoxLayout* aiFrameLayout = qobject_cast<QVBoxLayout*>(aiBackingFrame->layout());
        if (aiFrameLayout) {
            aiFrameLayout->insertWidget(1, aiPlayer);
        }
    }

    // Reset flags
    aiFinished = false;
    playerFinished = false;

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

    } else {
        gameResultLabel->setText("You won the race!");
    }
}
