/*
*****************************************************************************
                             Workshop - #1 DIY
Full Name  : NONTHACHAI PLODTHONG
Student ID#: 152487211
Email      : nplodthong@myseneca.ca
Section    : NII

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#ifndef W1P2_QUIZ_H
#define W1P2_QUIZ_H

#include <vector>
#include <iostream>

namespace quizzer {

    struct Choice {
        std::string choiceText;
        bool ifCorrect;
    };

    struct Question {
        std::string questionText;
        int typeQuestion; // type ma or mc
        std::vector<Choice> choiceList;
        unsigned int userAnswer = 0; // [X]
    };

    struct Quiz {
        std::vector<Question *> questionList;
    };

    int LoadQuiz(const char *filename);

    int IsQuizValid();

    int HasMoreQuestions();

    void ShowNextQuestion();

    void ShowQuizResults();




}

#endif //W1P2_QUIZ_H
