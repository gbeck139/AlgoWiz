#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter> // for bg image
#include <QPixmap>
#include <QMediaPlayer> // for music
#include <QAudioOutput>
#include <QUrl>
#include <QDir>
#include <QList>
#include <QPushButton>

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
    QList<QPushButton*> algoButtons = {ui->dfsWindowButton, ui->runtimeWindowButton};
    QList<QWidget*> algoWindows = {new DFSWindow(), new RuntimeWindow()};

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
void MainWindow::openDFS(){

}





void MainWindow::setStyle(QPushButton* btn){
    btn->setFlat(true);  // Removes 3D effect
    btn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: 2px solid #FFA500; /* Fiery orange */
            border-radius: 4px;
            font-size: 20px;
            font-weight: bold;
            font-style: italic;
            color: #FFA500;
        }

        QPushButton:hover {
            color: #FF4500; /* Brighter gold on hover */
            border-color: #FF4500;
        }

        QPushButton:checked {
            color: #FF6347; /* Highlighted red for selected */
            border-color: #FF6347;
            background-color: rgba(255, 99, 71, 0.1);
        }
    )");
    btn->setCheckable(true); // Allows the button to be "selected"
}
