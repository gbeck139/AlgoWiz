#include "mainwindow.h"
#include <QAudioOutput>
#include <QDir>
#include <QList>
#include <QMediaPlayer> // for music
#include <QPainter>     // for bg image
#include <QPixmap>
#include <QPushButton>
#include <QUrl>
#include <QGuiApplication> // for automatic resizing of window
#include <QScreen>
#include <QRect>
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
#include "lessonwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int newWidth = 0;
    int newHeight = 0;
    adjustWindowSize(this, newWidth, newHeight);

    // music
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.50);
    player->setAudioOutput(audioOutput);

    // Will take a few seconds to build first time around)
    player->setSource(QUrl("qrc:/audios/cool.mp3")); // simply change song name to either 'calm.mp3', 'cool.mp3', or 'hype.mp3'
    player->play();

    //automatic positioning of buttons for user specific screen size
    ui->runtimeWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 60, 150, 30);
    ui->graphTheoryWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 100, 150, 30);
    ui->binarySearchWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 140, 150, 30);

    ui->insertionSortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 60, 150, 30);
    ui->mergesortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 100, 150, 30);
    ui->stalinSortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 140, 150, 30);

    ui->dfsWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 60, 150, 30);
    ui->bfsWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 100, 150, 30);
    ui->dijkstraWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 140, 150, 30);

    ui->sortingGameWindowButton->setGeometry(newWidth/3.5 + 640, newHeight/1.5 + 60, 150, 30);
    ui->graphGameWindowButton->setGeometry(newWidth/3.5 + 640, newHeight/1.5 + 120, 150, 30);

    ui->label->setGeometry(newWidth/2.3, -350, 1000, 1000);
    ui->progressBar->setGeometry(newWidth/2.8, newHeight/20, 500, 100);
    ui->label_3->setGeometry(newWidth/3.3, newHeight/20, 500, 100);

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

    // Save as lambdas so that the animation in the window do not begin running yet
    QList<std::function<QWidget*()>> windowFactories = {
        [](){ return new LessonWindow(new DFSWindow,
                                       ":/images/purpleWizard.png"); },
        [](){ return new LessonWindow(new RuntimeWindow,
                                       ":/images/lightningWizard.png"); },
        [](){ return new LessonWindow(new MergeSortWindow,
                                       ":/images/darkWizard.png"); },
        [](){
            auto *lesson = new LessonWindow(
                new InsertionSortRenderer,
                ":/images/heavenlyWizard.png");
            lesson->setBannerText(
                "Insertion sort: in the best case, it's O(n), in the average "
                "and worst case, it's O(n^2). It accomplishes"
                " its best case with a conditional inner while-loop that checks if, "
                "in this case, the bar is already in its correct position."
                " It grows a \"sorted\" portion at each outer loop iteration, and "
                "then moves the rightmost bar to its proper place."
                );
            return lesson;
        },
        [](){ return new LessonWindow(new StalinSortWindow,
                                       ":/images/stalinWizard.png"); },
        [](){ return new LessonWindow(new GraphTheoryWindow,
                                       ":/images/colorfulWizard.png"); },
        [](){ return new LessonWindow(new BFSWindow,
                                       ":/images/smokeWizard.png"); },
        [](){ return new LessonWindow(new DijkstraWindow,
                                       ":/images/oldWizard.png"); },
        [](){ return new LessonWindow(new BinarySearchWindow,
                                       ":/images/greenWizard.png"); },
        [](){ return new LessonWindow(new SortingGameWindow,
                                       ":/images/wizard_sortgame.png"); },
        [](){ return new LessonWindow(new GraphGameWindow,
                                       ":/images/wizard_graphgame.png"); }
    };

    // set up for progress meter
    totalTasks = algoButtons.size();
    seen.fill(false, totalTasks);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    progressPercentLabel = ui->progressPercentLabel
                               ? ui->progressPercentLabel
                               : new QLabel("00%", this);

    if (!ui->progressPercentLabel) {
        progressPercentLabel->setGeometry(995, 40, 50, 23);
        progressPercentLabel->setAlignment(Qt::AlignCenter);
    }
    progressPercentLabel->setText("00%");



    for (int i = 0; i < algoButtons.size(); ++i) {
        QPushButton *button = algoButtons[i];
        auto factory = windowFactories[i];

        setStyle(button);
        connect(button, &QPushButton::clicked, this, [this, factory, i]() {

            if (!seen[i]) {
                seen[i] = true;
                completed += 1;
                int pct = completed * 100 / totalTasks;
                ui->progressBar->setValue(pct);
                QString txt = QString("%1%").arg(pct, 2, 10, QChar('0'));
                progressPercentLabel->setText(txt);

            }

            QWidget *win = factory();
            win->show();
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
    // btn->setFlat(true);  // Removes 3D effect
    // btn->setStyleSheet(R"(
    //     QPushButton {
    //         background-color: transparent;
    //         border: 2px solid #FFA500; /* Fiery orange */
    //         border-radius: 2px;
    //         font-size: 20px;
    //         font-weight: bold;
    //         font-style: italic;
    //         color: #FFA500;
    //     }

    //     QPushButton:hover {
    //         color: #FF4500; /* Brighter gold on hover */
    //         border-color: #FF4500;
    //     }
    // )");


    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(R"(
        QPushButton {
            background:rgba(255,165,0,0.15);
            border:2px solid #FFA500;
            border-radius:8px;
            color:#ffffff;
            font:700 18px 'Trebuchet MS';
        }
        QPushButton:hover {
            background:#FFA500;
            color:#000000;
        }
        QPushButton:pressed {
            background:#FF7B00;
            color:#000000;
        }
    )");
    btn->setCheckable(true);
}

void MainWindow::adjustWindowSize(QWidget* window, int &newWidth, int &newHeight)
{
    QScreen* screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        QRect availableGeometry = screen->availableGeometry();

        newWidth = availableGeometry.width();
        newHeight = availableGeometry.height();

        setFixedSize(newWidth, newHeight);
        window->move(availableGeometry.center() - window->frameGeometry().center());
    }
}
