/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class, which handles the main UI, navigation between algorithm windows, and user progress tracking in the AlgoWiz educational app.
 * @author Jared Pratt, Grant Beck, Isaac Huntsman, Joshua Eggett, Woojin Lee, David Perry
 * @date 2025-04-25
 */

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
#include "graphtheorywindow.h"
#include "graphtraversalgamewindow.h"
#include "insertionsortwindow.h"
#include "mergesortwindow.h"
#include "quizwindow.h"
#include "sortinggamewindow.h"
#include "stalinsortwindow.h"
#include "ui_mainwindow.h"
#include "lessonwindow.h"
#include "ButtonPhysics.h"

// Constructor: sets up UI, music, button styles, animations, and connects navigation logic
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int newWidth = 0;
    int newHeight = 0;
    adjustWindowSize(this, newWidth, newHeight);

    // Background music setup
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.50);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/audios/cool.mp3")); // simply change song name to either 'calm.mp3', 'cool.mp3', or 'hype.mp3'
    player->play();

    // Button positioning based on dynamic screen size
    ui->runtimeWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 60, 150, 30);
    ui->graphTheoryWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 100, 150, 30);
    ui->binarySearchWindowButton->setGeometry(newWidth/8.5 + 100, newHeight/1.5 + 140, 150, 30);

    ui->insertionSortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 60, 150, 30);
    ui->mergesortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 100, 150, 30);
    ui->stalinSortWindowButton->setGeometry(newWidth/8.5 + 270, newHeight/1.5 + 140, 150, 30);

    ui->dfsWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 60, 150, 30);
    ui->bfsWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 100, 150, 30);
    ui->dijkstraWindowButton->setGeometry(newWidth/8.5 + 440, newHeight/1.5 + 140, 150, 30);

    ui->practiceQuizWindowButton->setGeometry(newWidth/3.5 + 640, newHeight/1.5 + 60, 150, 30);
    ui->sortingGameWindowButton->setGeometry(newWidth/3.5 + 640, newHeight/1.5 + 100, 150, 30);
    ui->graphGameWindowButton->setGeometry(newWidth/3.5 + 640, newHeight/1.5 + 140, 150, 30);

    ui->label->setGeometry(newWidth/2.3, -350, 1000, 1000);
    ui->progressBar->setGeometry(newWidth/2.8, newHeight/20, 500, 100);
    ui->label_3->setGeometry(newWidth/3.3 - 20, newHeight/20, 500, 100);
    ui->progressPercentLabel->setGeometry(newWidth/1.4, newHeight/20, 500, 100);

    // Algorithm buttons list
    QList<QPushButton *> algoButtons = {ui->dfsWindowButton,
                                        ui->runtimeWindowButton,
                                        ui->mergesortWindowButton,
                                        ui->insertionSortWindowButton,
                                        ui->stalinSortWindowButton,
                                        ui->graphTheoryWindowButton,
                                        ui->bfsWindowButton,
                                        ui->dijkstraWindowButton,
                                        ui->binarySearchWindowButton,
                                        ui->practiceQuizWindowButton,
                                        ui->sortingGameWindowButton,
                                        ui->graphGameWindowButton};

    new ButtonPhysics(this, algoButtons);

    // Window factory functions (deferred creation)
    QList<std::function<QWidget*()>> windowFactories = {
        // DFS
        []() {
            auto *lesson = new LessonWindow(new DFSWindow,
                                            ":/images/purpleWizard.png");
            lesson->setBannerText(
                "Depth‑First Search (DFS)\n\n"
                "Depth‑First Search (DFS) is a graph traversal algorithm that explores as far as possible along "
                "each branch before backtracking. It uses a stack—either via recursion or an explicit stack—to "
                "remember the path. DFS runs in O(V + E) time and requires O(V) space for the stack.\n\n"
                "- Explores depth‑first with backtracking\n"
                "- Uses recursion or explicit stack\n"
                "- Time: O(V + E), Space: O(V)\n"
                "- Good for cycle detection & topological sort\n"
                "- Solves maze‑like puzzles"
                );
            return lesson;
        },

        // Runtime Complexity
        []() {
            auto *lesson = new LessonWindow(new RuntimeWindow,
                                            ":/images/lightningWizard.png");
            lesson->setBannerText(
                "Runtime Complexity (Big‑O)\n\n"
                "Runtime complexity measures how an algorithm’s execution time grows as the input size increases. "
                "Using Big‑O notation we classify algorithms by their upper‑bound growth rates.\n\n"
                "- O(1): constant time\n"
                "- O(log n): logarithmic time\n"
                "- O(n): linear time\n"
                "- O(n log n): linearithmic time\n"
                "- O(n^2): quadratic time\n"
                "- Visualization compares growth curves"
                );
            return lesson;
        },

        // Merge Sort
        []() {
            auto *lesson = new LessonWindow(new MergeSortWindow,
                                            ":/images/darkWizard.png");
            lesson->setBannerText(
                "Merge Sort\n\n"
                "Merge sort is an O(NLogN) in all cases sorting algorithm that is O(N) in space "
                "complexity. It starts by splitting a list into elements of size 1, and then merging each "
                "of those lists back together, swapping the ordering along the way as needed. This "
                "visualization shows the \"second half\" of the sort, and sorts the left subtrees first.\n\n"
                "- Time: O(n log n) in all cases\n"
                "- Space: O(n) extra\n"
                "- Recursively splits into size‑1 lists\n"
                "- Merges by comparing and appending smaller elements\n"
                "- Divide‑and‑conquer approach"
                );
            return lesson;
        },

        // Insertion Sort
        []() {
            auto *lesson = new LessonWindow(new InsertionSortWindow,
                                            ":/images/heavenlyWizard.png");
            lesson->setBannerText(
                "Insertion Sort \n\n"
                "Insertion sort: in the best case, it's O(n), in the average "
                "and worst case, it's O(n^2). It accomplishes"
                "its best case with a conditional inner while-loop that checks if, "
                "in this case, the bar is already in its correct position."
                "It grows a \"sorted\" portion at each outer loop iteration, and "
                "then moves the rightmost bar to its proper place..\n\n"
                "- Best: O(n), Average/Worst: O(n^2)\n"
                "- Builds sorted portion one element at a time\n"
                "- Uses conditional inner while‑loop to shift\n"
                "- In‑place and stable\n"
                "- Efficient on small or mostly‑sorted data"
                );
            return lesson;
        },

        // Stalin Sort
        []() {
            auto *lesson = new LessonWindow(new StalinSortWindow,
                                            ":/images/stalinWizard.png");
            lesson->setBannerText(
                "Stalin Sort \n\n"
                "Stalin sort: It is always O(N) and works by 'taking out back' unsorted elements. "
                "It is in place as well so it has constant memory (actually frees more up?!?). "
                "This makes stalin sort one of the 'best' sorting algorithms if you are fine with "
                "missing data at the end.\n\n"
                "- Time: O(n)\n"
                "- In‑place with constant extra space\n"
                "- Removes out‑of‑order elements\n"
                "- Discards missing data at the end\n"
                "- Fastest if discarding values is acceptable"
                );
            return lesson;
        },

        // Graph Theory
        []() {
            auto *lesson = new LessonWindow(new GraphTheoryWindow,
                                            ":/images/colorfulWizard.png");
            lesson->setBannerText(
                "Graph Theory \n\n"
                "Graph theory studies structures of nodes (vertices) connected by edges. Graphs model networks "
                "such as social connections, road maps, and communication links.\n\n"
                "- A, B, C, D, and E are vertices. Edges connect BC and DE\n"
                "- Vertices can hold data: D has value 5\n"
                "- Edges can also be weighted (DE has weight 6) or unweighted (BC)\n"
                "- Traversals: BFS and DFS\n"
                "- Shortest paths & spanning trees"
                );
            return lesson;
        },

        // BFS
        []() {
            auto *lesson = new LessonWindow(new BFSWindow,
                                            ":/images/smokeWizard.png");
            lesson->setBannerText(
                "Breadth‑First Search (BFS)\n\n"
                "Breadth‑First Search (BFS) explores all neighbors of a vertex before moving deeper. "
                "It uses a queue to track the frontier.\n\n"
                "- Explores level by level\n"
                "- Uses a queue for the frontier\n"
                "- Time: O(V + E), Space: O(V)\n"
                "- Finds shortest paths in unweighted graphs\n"
                "- Useful for networking/routing"
                );
            return lesson;
        },

        // Dijkstra’s Algorithm
        []() {
            auto *lesson = new LessonWindow(new DijkstraWindow,
                                            ":/images/oldWizard.png");
            lesson->setBannerText(
                "Dijkstra’s Algorithm \n\n"
                "Dijkstra’s algorithm finds the shortest paths from a source to all vertices in a non‑negative "
                "weighted graph.\n\n"
                "- Requires non‑negative edge weights\n"
                "- Uses a min‑heap of distance estimates\n"
                "- Extracts closest vertex each step\n"
                "- Relaxes outgoing edges\n"
                "- Time: O((V + E) log V), Space: O(V)"
                );
            return lesson;
        },

        // Binary Search
        []() {
            auto *lesson = new LessonWindow(new BinarySearchWindow,
                                            ":/images/greenWizard.png");
            lesson->setBannerText(
                "Binary Search \n\n"
                "Binary search is an algorithm used to quickly find a target value within a sorted list. "
                "The main idea is to repeatedly divide the search range in half. First, it checks the middle element of the list. "
                "If the target value is greater than the middle element, the algorithm continues searching in the right half. "
                "On the other hand, if it's smaller, it searches the left half. "
                "This process continues until the target is found or there are no more elements left to check. "
                "The runtime of the binary serach is O(1) in the best case, O(log n) in the worst case. "
                "The bar below is a way to find the number 14 using binary search among bars 1 to 20.\n\n"
                "- Requires sorted list\n"
                "- Check middle element first\n"
                "- If target > middle, search right half\n"
                "- Else search left half\n"
                "- Best: O(1), Average/Worst: O(log n)"
                );
            return lesson;
        },

        // Quiz (no banner text)
        []() {
            return new LessonWindow(new QuizWindow,
                                    ":/images/bookWizard", false);
        },

        // Sorting Game (no banner text)
        []() {
            return new LessonWindow(new SortingGameWindow,
                                    ":/images/snowWizard.png", false);
        },

        // Graph Game (no banner text)
        []() {
            return new LessonWindow(new GraphTraversalGameWindow,
                                    ":/images/vikingWizard.png", false);
        }
    };

    // Initialize progress tracking
    totalTasks = algoButtons.size();
    seen.fill(false, totalTasks);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    progressPercentLabel = ui->progressPercentLabel
                               ? ui->progressPercentLabel
                               : new QLabel("0%", this);

    if (!ui->progressPercentLabel) {
        // progressPercentLabel->setGeometry(995, 40, 50, 23);
        progressPercentLabel->setAlignment(Qt::AlignCenter);
    }
    progressPercentLabel->setText("0%");

    // Connect buttons to their respective windows and update progress tracking
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

// Custom background image rendering
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

// Sets button styles (hover, pressed, default)
void MainWindow::setStyle(QPushButton* btn){
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

// Adjusts the main window size to fit the screen
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
