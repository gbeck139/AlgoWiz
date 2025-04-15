#include "mainwindow.h"
#include <QAudioOutput>
#include <QDir>
#include <QList>
#include <QMediaPlayer> // for music
#include <QPainter>     // for bg image
#include <QPixmap>
#include <QPushButton>
#include <QUrl>
#include "bfswindow.h"
#include "binarysearchwindow.h"
#include "dijkstrawindow.h"
#include "graphgamewindow.h"
#include "graphtheorywindow.h"
#include "insertionsortwindow.h"
#include "mergesortwindow.h"
#include "sortinggamewindow.h"
#include "stalinsortwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1375, 875);

    // music
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.25);
    player->setAudioOutput(audioOutput);
    // Will take a few seconds to build first time around)
    player->setSource(QUrl("qrc:/audios/cool.mp3")); // simply change song name to either 'calm.mp3', 'cool.mp3', or 'hype.mp3'
    player->play();


    // Algorithm windows and buttons
    QList<QPushButton *> algoButtons = {ui->dfsWindowButton,
                                        ui->runtimeWindowButton,
                                        ui->mergesortWindowButton,
                                        ui->insertionSortWindowButton,
                                        ui->stalinSortWindowButton,
                                        ui->graphTheoryWindowButton,
                                        ui->bfsWindowButton,
                                        ui->dijkstraWindowButton,
                                        ui->binarySearchWindowButton,
                                        ui->sortingGameWindowButton,
                                        ui->graphGameWindowButton};
    QList<QWidget *> algoWindows = {new DFSWindow(),
                                    new RuntimeWindow(),
                                    new MergeSortWindow(),
                                    new InsertionSortWindow(),
                                    new StalinSortWindow(),
                                    new GraphTheoryWindow(),
                                    new BFSWindow(),
                                    new DijkstraWindow(),
                                    new BinarySearchWindow(),
                                    new SortingGameWindow(),
                                    new GraphGameWindow()};

    // Set Button Styles and connect to windows
    for (int i = 0; i < algoButtons.size(); ++i) {
        QPushButton *button = algoButtons[i];
        QWidget *window = algoWindows[i];

        setStyle(button);
        connect(button, &QPushButton::clicked, this, [window]() {
            window->show();
        });
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

// background image
void MainWindow::paintEvent(QPaintEvent *event){
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    QPixmap bg(":/images/AlgoWiz wizard.png");
    if (!bg.isNull())
    {
        QSize targetSize = bg.size();
        targetSize.scale(size(), Qt::KeepAspectRatio);

        QPixmap scaled = bg.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;
        painter.drawPixmap(x, y, scaled);
    }
}

// Algorithm Windows
// void MainWindow::openDFS(){

// }

void MainWindow::setStyle(QPushButton* btn){
    btn->setFlat(true);  // Removes 3D effect
    btn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: 2px solid #FFA500; /* Fiery orange */
            border-radius: 2px;
            font-size: 20px;
            font-weight: bold;
            font-style: italic;
            color: #FFA500;
        }

        QPushButton:hover {
            color: #FF4500; /* Brighter gold on hover */
            border-color: #FF4500;
        }
    )");
    btn->setCheckable(true); // Allows the button to be "selected"
}
