#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter> // for bg image
#include <QPixmap>
#include <QMediaPlayer> // for music
#include <QAudioOutput>
#include <QUrl>
#include <QDir>

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

    //Slower universal method ((will take a couple minutes to build first time around)
    player->setSource(QUrl("qrc:/audios/cool.mp3")); // simply change song name to either 'calm.mp3', 'cool.mp3', or 'hype.mp3'



    // FASTER METHOD for loading audio

    // QString audioPath;
    // #ifdef Q_OS_MACOS
    // audioPath = QDir(QCoreApplication::applicationDirPath())
    //                 .filePath("../../../audios/cool.mp3");
    // #else
    // audioPath = QDir(QCoreApplication::applicationDirPath())
    //                 .filePath("audios/dope.mp3");
    // #endif
    // player->setSource(QUrl::fromLocalFile(audioPath));

    player->play();


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
