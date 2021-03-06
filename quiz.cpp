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
#include <iostream>
#include <fstream>
#include <memory>
#include "quiz.h"


using namespace std;
namespace quizzer {


    ifstream quizFile;
    struct Quiz *quizData;
    size_t questionIndex = 0;
    string ma = "{ma}";
    string mc = "{mc}";
    size_t loopDelete;


    int LoadQuiz(char const *filename) {
        string dataString;
        string substring;
        struct Question *question;
        quizFile.open(filename, ios::out);
        if (!quizFile) {
            return 1;
        } else {
            if (quizData != nullptr) {
                for (loopDelete = 0; loopDelete < quizData->questionList.size(); loopDelete++) {
                    question = quizData->questionList.at(loopDelete);
                    question->choiceList.clear();
                    question->questionText.clear();
                    delete question;

                }
                quizData->questionList.clear();
                delete quizData;
            }
            quizData = new struct Quiz; // create new data file every load
            while (getline(quizFile, dataString)) {
                if (dataString.length() == 0) {
                    continue;
                }
                if (dataString.at(0) == '{') {// Question
                    question = new struct Question; // mem leak
                    substring = dataString.substr(0, 4);
                    if (substring == mc) {
                        question->typeQuestion = 1; // 1 = mc
                    } else if (substring == ma) {
                        question->typeQuestion = 2; // 2 = ma
                    }
                    question->questionText = dataString.substr(5); // mem leak
                    quizData->questionList.push_back(question); // if line 34 // push_back ????????? string copy
                    // leak
                } else if (dataString.at(0) == '[') { // Choice
                    struct Choice choice;
                    if (dataString.at(1) == 'X') {
                        choice.ifCorrect = true;
                    } else {
                        choice.ifCorrect = false;
                    }
                    choice.choiceText = dataString.substr(4); // leak
                    question->choiceList.push_back(choice); // leak
                }
            }
            /*size_t i;
            for (i = 0; i < quizData->questionList.size(); i++) {
                struct Question *question1 = quizData->questionList.at(i);
                cout << endl << i << endl;

                cout << "deb " << question1->questionText << endl;
                size_t j;
                for (j = 0; j < question1->choiceList.size(); j++) {
                    cout << endl << j << endl;
                    cout << "deb " << question1->choiceList.at(j).choiceText << endl;
                }*/
        }

        quizFile.close();
        return 0;
    }


    int IsQuizValid() {
        struct Choice choice;
        struct Question *question;
        int countValid = 0;
        size_t i, j = 0;
        if (quizData->questionList.size() < 5) {
            return 0;
        }
        for (i = 0; i < quizData->questionList.size(); i++) {
            int correct = 0;
            question = quizData->questionList.at(i);
            for (j = 0; j < question->choiceList.size(); j++) {
                choice = question->choiceList.at(j);
                if (choice.ifCorrect) {
                    correct++;
                }
            }
            if (question->typeQuestion == 1) {
                if (correct == 1) {
                    //Question 1 -> OK
                    cout << "Question " << (i + 1) << " -> OK" << endl;
                    countValid++;
                } else {
                    cout << "Question " << (i + 1) << " -> ERROR" << endl;
                }
            } else if (question->typeQuestion == 2) {
                if (correct >= 1) {
                    cout << "Question " << (i + 1) << " -> OK" << endl;
                    countValid++;
                } else {
                    cout << "Question " << (i) << " -> ERROR" << endl;
                }
            }
        }
        if (countValid < 5) {
            return 0;
        }
        return 1;
    }

    int HasMoreQuestions() {

        questionIndex++;
        //quizData->questionList.at(questionIndex);
        if (questionIndex < quizData->questionList.size()) {  // ?????????????????????????????????????????????????????????????????????????????????
            return 1;
        } else {
            questionIndex = 0;
            return 0;
        }
    }

    void ShowNextQuestion() {
        string ss;
        size_t i;
        //new struct Choice;
        struct Choice choice;
        struct Question *question = quizData->questionList.at(questionIndex);
        cout << question->questionText << endl;
        for (i = 0; i < question->choiceList.size(); i++) {
            choice = question->choiceList.at(i); // ???????????????????????????????????????????????????????????????????????????????????? i ?????????????????????????????????????????? 0
            cout << (i + 1) << ". " << choice.choiceText << endl;
        }
        cout << "Your answer? ";
        cin >> question->userAnswer;
    }

    void ShowQuizResults() {
        struct Question *question = quizData->questionList.at(0);
        int checkCorrect = 0;
        int score = 0;
        size_t i = 0;
        for (i = 0; i < quizData->questionList.size(); i++) {
            struct Question *question1 = quizData->questionList.at(i);
            if (question->userAnswer <= question1->choiceList.size()) {
                if (question->userAnswer == 0) {
                    question->userAnswer++;
                    checkCorrect = +1;
                }
                struct Choice choice = question1->choiceList.at(question->userAnswer - 1);
                if (choice.ifCorrect) {
                    score++;
                }
            }
        }
        if (score != 0) {
            if (checkCorrect == 0) {
                cout << endl << "QUIZ RESULTS: your score is "
                     << score << "/"
                     << quizData->questionList.size()
                     << "." << endl;
            }
        }
    }


}

