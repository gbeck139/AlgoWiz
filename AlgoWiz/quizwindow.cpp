#include <QLabel>
#include <QVBoxLayout>
#include "quizwindow.h"
#include <QRandomGenerator>

QuizWindow::QuizWindow(QWidget *parent)
    : QWidget(parent) {

    resize(600, 500);
    layout = new QVBoxLayout(this);
    optionFont.setPointSize(24);

    // Intro screen
    introLabel = new QLabel("Are you ready for the quiz?", this);
    introLabel->setAlignment(Qt::AlignCenter);
    introLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: white;");

    layout->addWidget(introLabel);

    startQuizButton = new QPushButton("Ready to Quiz", this);
    layout->addWidget(startQuizButton);

    // Quiz setup
    quizLabel = new QLabel(this);
    quizLabel->setWordWrap(true);
    layout->addWidget(quizLabel);

    optionA = new QRadioButton(this);
    optionB = new QRadioButton(this);
    optionC = new QRadioButton(this);
    optionD = new QRadioButton(this);

    optionA->setFont(optionFont);
    optionB->setFont(optionFont);
    optionC->setFont(optionFont);
    optionD->setFont(optionFont);

    optionsGroup = new QButtonGroup(this);
    optionsGroup->addButton(optionA, 0);
    optionsGroup->addButton(optionB, 1);
    optionsGroup->addButton(optionC, 2);
    optionsGroup->addButton(optionD, 3);

    layout->addWidget(optionA);
    layout->addSpacing(12);
    layout->addWidget(optionB);
    layout->addSpacing(12);
    layout->addWidget(optionC);
    layout->addSpacing(12);
    layout->addWidget(optionD);

    resultLabel = new QLabel(this);
    layout->addWidget(resultLabel);

    nextQuizButton = new QPushButton("Next", this);
    layout->addWidget(nextQuizButton);

    // Hide quiz components initially
    quizLabel->hide();
    optionA->hide();
    optionB->hide();
    optionC->hide();
    optionD->hide();
    resultLabel->hide();
    nextQuizButton->hide();

    connect(startQuizButton, &QPushButton::clicked, this, [this]() {
        introLabel->hide();
        startQuizButton->hide();
        initializeQuizzes();
        showQuizWidgets();
        showRandomQuiz();
    });

    connect(nextQuizButton, &QPushButton::clicked, this, &QuizWindow::showRandomQuiz);
    connect(optionsGroup, &QButtonGroup::idClicked, this, &QuizWindow::checkAnswer);
}

void QuizWindow::showQuizWidgets() {
    quizLabel->show();
    optionA->show();
    optionB->show();
    optionC->show();
    optionD->show();
    resultLabel->show();
    nextQuizButton->show();
}

void QuizWindow::initializeQuizzes() {
    allQuizzes = {
        [this]() { DFSQuiz(); },
        [this]() { BFSQuiz(); },
        [this]() { InsertionSortQuiz(); },
        [this]() { StalinSortQuiz(); },
        [this]() { MergeSortQuiz(); },
        [this]() { DijkstraQuiz(); },
        [this]() { BinarySearchQuiz(); }
    };

    remainingIndices.clear();
    for (int i = 0; i < allQuizzes.size(); ++i)
        remainingIndices.append(i);
}

void QuizWindow::showRandomQuiz() {
    // erase the previous quetions answer color.
    QList<QRadioButton*> options = {optionA, optionB, optionC, optionD};
    for (auto* btn : options) {
        btn->setStyleSheet("");
        btn->setChecked(false);
        btn->setEnabled(true);
    }

    // After finish the quiz
    if (remainingIndices.isEmpty()) {
        quizLabel->setText(
            QString("All questions completed!\nYou got %1 out of %2 correct!")
                .arg(score)
                .arg(allQuizzes.size())
            );
        optionA->hide();
        optionB->hide();
        optionC->hide();
        optionD->hide();
        resultLabel->clear();
        nextQuizButton->setEnabled(false);
        return;
    }

    resultLabel->clear();
    optionsGroup->setExclusive(false);
    optionA->setChecked(false);
    optionB->setChecked(false);
    optionC->setChecked(false);
    optionD->setChecked(false);
    optionsGroup->setExclusive(true);

    int randIndex = QRandomGenerator::global()->bounded(remainingIndices.size());
    int quizIndex = remainingIndices[randIndex];
    remainingIndices.removeAt(randIndex);

    allQuizzes[quizIndex]();
}

void QuizWindow::DijkstraQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Which of the following is a correct characteristic of Dijkstra’s algorithm?");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) It can be used on graphs with \"negative edge\" weights");
    optionB->setText("B) It uses a stack to select the next closest vertex");
    optionC->setText("C) It finds the shortest paths from a source to all other vertices in a graph with non-negative weights");
    optionD->setText("D) The runtime complexity is O(V)");

    correctAnswerIndex = 2;
}

void QuizWindow::MergeSortQuiz(){
    setWindowTitle("MergeSort quiz");

    //Set the question
    quizLabel->setText("Which of the following is true about Merge Sort?");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) It always runs in O(n²) time");
    optionB->setText("B) It compares all elements with each other at once");
    optionC->setText("C) It only works on already sorted lists.");
    optionD->setText("D) It splits the list into smaller parts and merges them in order");

    correctAnswerIndex = 3;
}

void QuizWindow::DFSQuiz(){
    setWindowTitle("DFS quiz");

    //Set the question
    quizLabel->setText("Which of the following is true about Depth-First Search (DFS)");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) Visits nodes by going as deep as possible before backtracking");
    optionB->setText("B) Visits all neighbors of a node before moving to the next level.");
    optionC->setText("C) It compares all elements with each other at once");
    optionD->setText("D) Runtime is O(VE)");

    correctAnswerIndex = 0;
}

void QuizWindow::BFSQuiz(){
    setWindowTitle("BFS quiz");

    //Set the question
    quizLabel->setText("Which of the following is true about Breadth-First Search (BFS)");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) Visits nodes by going as deep as possible before backtracking");
    optionB->setText("B) Visits all neighbors of a node before moving to the next level.");
    optionC->setText("C) It compares all elements with each other at once");
    optionD->setText("D) Runtime is O(VE)");

    correctAnswerIndex = 1;
}

void QuizWindow::InsertionSortQuiz(){
    setWindowTitle("InsertionSort quiz");

    //Set the question
    quizLabel->setText("Which of the following is true about Insertion Sort?");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) It inserts each element into its correct position in the sorted part");
    optionB->setText("B) It swaps random elements");
    optionC->setText("C) It compares all elements with each other at once");
    optionD->setText("D) The worst runtime is O(n)");

    correctAnswerIndex = 0;
}

void QuizWindow::StalinSortQuiz(){
    setWindowTitle("StalinSort quiz");

    //Set the question
    quizLabel->setText("What is correct answer for the stalin sort?");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) It merges sorted subarrays to create the final result");
    optionB->setText("B) It removes any element that is smaller than the previous one");
    optionC->setText("C) It keeps all elements, and sort it");
    optionD->setText("D) It inserts each element into its correct position in the sorted part");

    correctAnswerIndex = 1;
}

void QuizWindow::BinarySearchQuiz() {
    setWindowTitle("BinarySearch quiz");

    //Set the question
    quizLabel->setText("What is the runtime of the worst case in the binary search?");
    quizLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    //Set the option
    optionA->setText("A) O(1)");
    optionB->setText("B) O(logn)");
    optionC->setText("C) O(n)");
    optionD->setText("D) O(n^2)");

    correctAnswerIndex = 1;
}

void QuizWindow::checkAnswer(int id) {
    QList<QRadioButton*> options = {optionA, optionB, optionC, optionD};

    for (auto* btn : options)
        btn->setStyleSheet("");

    if (id == correctAnswerIndex) {
        options[id]->setStyleSheet("color: white; background-color: green;");
        score++;
    } else {
        options[id]->setStyleSheet("color: white; background-color: red;");
        options[correctAnswerIndex]->setStyleSheet("color: white; background-color: green;");
    }

    // Make user can decide the answer only one time.
    for (auto* btn : options)
        btn->setEnabled(false);
}
