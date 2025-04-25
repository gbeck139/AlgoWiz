/**
 * @file quizwindow.h
 * @author Woojin Lee, Davide Perry
 * @brief This file contains the declaration of the QuizWindow class to create the quiz for algorithms.
 * @date 2025-04-24
 */

#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

class QuizWindow : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief QuizWindow - constructs a QuizWindow
     * @param parent The parent widget
     */
    QuizWindow(QWidget *parent = nullptr);

    /**
     * @brief DijkstraQuiz - Quiz for Dijkstra.
     */
    void DijkstraQuiz();

    /**
     * @brief MergeSortQuiz - Quiz for Merge Sort.
     */
    void MergeSortQuiz();

    /**
     * @brief DFSQuiz - Quiz for DFS.
     */
    void DFSQuiz();

    /**
     * @brief BFSQuiz - Quiz for BFS.
     */
    void BFSQuiz();

    /**
     * @brief InsertionSortQuiz - Quiz for Insertion Sort.
     */
    void InsertionSortQuiz();

    /**
     * @brief StalinSortQuiz - Quiz for Stalin Sort.
     */
    void StalinSortQuiz();

    /**
     * @brief BinarySearchQuiz - Quiz for Binary Search.
     */
    void BinarySearchQuiz();

private slots:
    /**
     * @brief checkAnswer - Called when a radio button is clicked.
     * @param id - Checks if the selected answer is correct.
     */
    void checkAnswer(int id);

    /**
     * @brief showRandomQuiz - Shows a random quiz.
     */
    void showRandomQuiz();

    /**
     * @brief showQuizWidgets - Makes the quiz UI elements (question + options) visible.
     */
    void showQuizWidgets();

    /**
     * @brief initializeQuizzes - Initializes the list of quiz methods and resets the quiz state.
     */
    void initializeQuizzes();

private:
    /**
     * @brief introLabel - Initializes the list of quiz methods, resets the quiz state and show the intro message.
     */
    QLabel *introLabel;

    /**
     * @brief startQuizButton - Button to start quiz.
     */
    QPushButton *startQuizButton;

    /**
     * @brief nextQuizButton - Button to move to next quiz.
     */
    QPushButton *nextQuizButton;

    /**
     * @brief quizLabel - Display quiz question.
     */
    QLabel *quizLabel;

    /**
     * @brief quizLabel - Set the result label section.
     */
    QLabel *resultLabel;

    /**
     * @brief Layout for arranging all widgets vertically.
     */
    QVBoxLayout *layout;

    /**
     * @brief optionA - 1st answer option.
     */
    QRadioButton *optionA;

    /**
     * @brief optionB - 2nd answer option.
     */
    QRadioButton *optionB;

    /**
     * @brief optionC - 3rd answer option.
     */
    QRadioButton *optionC;

    /**
     * @brief optionD - 4th answer option.
     */
    QRadioButton *optionD;

    /**
     * @brief optionsGroup - Groups the radio buttons and tracks the selected option.
     */
    QButtonGroup *optionsGroup;

    /**
     * @brief correctAnswerIndex - Index (0 to 3) of the correct answer for the current question.
     */
    int correctAnswerIndex;

    /**
     * @brief allQuizzes - List of all available quiz setup functions.
     */
    QList<std::function<void()>> allQuizzes;

    /**
     * @brief remainingIndices - Indices of remaining quizzes not yet shown.
     */
    QList<int> remainingIndices;

    /**
     * @brief optionFont - Font used for displaying option.
     */
    QFont optionFont;

    /**
     * @brief score - check the user score how many question they got.
     */
    int score = 0;
};

#endif // QUIZWINDOW_H
