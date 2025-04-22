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
    QuizWindow(QWidget *parent = nullptr);

    void binarySearchQuiz();

private slots:
    void checkAnswer(int id);

private:
    QLabel *quizLabel;
    QLabel *resultLabel;

    QVBoxLayout *layout;
    QRadioButton *optionA;
    QRadioButton *optionB;
    QRadioButton *optionC;
    QRadioButton *optionD;
    QButtonGroup *optionsGroup;

    int correctAnswerIndex;
};

#endif // QUIZWINDOW_H
