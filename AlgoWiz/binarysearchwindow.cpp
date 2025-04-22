#include "binarysearchwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include "binarysearchrenderer.h"

BinarySearchWindow::BinarySearchWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("BinarySearch");
    resize(600, 500);

    // Create a layout for the window
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the title label
    QLabel *label = new QLabel("Binary search is an algorithm used to quickly find a target value within a sorted list. "
                               "The main idea is to repeatedly divide the search range in half. First, it checks the middle element of the list. "
                               "If the target value is greater than the middle element, the algorithm continues searching in the right half. "
                               "On the other hand, if it's smaller, it searches the left half. "
                               "This process continues until the target is found or there are no more elements left to check. "
                               "The runtime of the binary serach is O(1) in the best case, O(log n) in the worst case. "
                               "The bar below is a way to find the number 14 using binary search among bars 1 to 20.",
                               this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);

    // Create the BinarySearchRenderer
    renderer = new BinarySearchRenderer();
    renderer->setMinimumHeight(300);

    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(renderer);

    // Quiz button.
    nextButton = new QPushButton("Ready to take a quiz", this);
    layout->addWidget(nextButton);
    connect(nextButton, &QPushButton::clicked, [this]() {
        quizWindow->binarySearchQuiz();
        quizWindow->show();
        this->hide();
    });

    // Set the layout
    setLayout(layout);
}

