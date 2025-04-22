#include <QLabel>
#include <QVBoxLayout>
#include "quizwindow.h"

QuizWindow::QuizWindow(QWidget *parent)
    : QWidget(parent) {

    resize(600, 500);

    layout = new QVBoxLayout(this);

    // Set question
    quizLabel = new QLabel(this);
    quizLabel->setWordWrap(true);

    layout->addWidget(quizLabel);

    // Set 4 options
    optionA = new QRadioButton(this);
    optionB = new QRadioButton(this);
    optionC = new QRadioButton(this);
    optionD = new QRadioButton(this);

    optionsGroup = new QButtonGroup(this);
    optionsGroup->addButton(optionA, 0);
    optionsGroup->addButton(optionB, 1);
    optionsGroup->addButton(optionC, 2);
    optionsGroup->addButton(optionD, 3);

    layout->addWidget(optionA);
    layout->addWidget(optionB);
    layout->addWidget(optionC);
    layout->addWidget(optionD);

    //Set result
    resultLabel = new QLabel(this);
    layout->addWidget(resultLabel);

    connect(optionsGroup, &QButtonGroup::idClicked, this, &QuizWindow::checkAnswer);
}


void QuizWindow::DijkstraQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::MergeSortQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::DFSQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::BFSQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::InsertionSortQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::StalinSortQuiz(){
    setWindowTitle("Dijkstra quiz");

    //Set the question
    quizLabel->setText("Quesiton?");

    //Set the option
    optionA->setText("A)");
    optionB->setText("B)");
    optionC->setText("C)");
    optionD->setText("D)");

    correctAnswerIndex = 0;

    resultLabel->clear();
}

void QuizWindow::BinarySearchQuiz() {
    setWindowTitle("BinarySearch quiz");

    //Set the question
    quizLabel->setText("What is the runtime of the worst case in the binary search?");

    //Set the option
    optionA->setText("A) O(1)");
    optionB->setText("B) O(logn)");
    optionC->setText("C) O(n)");
    optionD->setText("D) O(n^2)");

    correctAnswerIndex = 1;

    resultLabel->clear();
}

void QuizWindow::checkAnswer(int id) {
    if (id == correctAnswerIndex) {
        resultLabel->setText("Correct!");
    } else {
        resultLabel->setText("Incorrect. Study hard and Try again.");
    }
}
