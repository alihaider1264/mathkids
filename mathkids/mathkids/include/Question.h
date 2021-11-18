#ifndef _QUESTION_
#define _QUESTION_

#include <string>
#include <vector>
#include <fstream>
#include "Split.h"

class Question{
	int operand1;
	int operand2;
	char op;
    bool isTextual;
    std::string text;
    int result;
    std::vector<std::string> text_questions;

public:
    Question():
            operand1(0), operand2(0), op(' '), isTextual(false), text(""), result(0){}
    Question(int op1, int op2, char oper, bool isText, std::string txt):
            operand1(op1), operand2(op2), op(oper), isTextual(isText), text(txt), result(0){
        //read textual questions
        std::string line;
        std::ifstream f;
        f.open("_data/textual_questions.csv");
		if (f.is_open()) {
			while (f) {
				std::getline(f, line);
				text_questions.push_back(line);
			}
		}
		else {
			std::cout << "Couldn't open _data/textual_questions.dat file\n";
		}
		//
		f.close();
            }

    int getResult() { return result; }
    bool isText() { return isTextual; }
    std::string getText() { return text; }
    int getOperand1() { return operand1; }
    int getOperand2() { return operand2; }
    char getOperator() { return op; }
    bool setResult(int res) { result = res; return true;}
    Question selectRandomTextQuestion();
    void printQuestions();
    ~Question(){}

};


Question Question::selectRandomTextQuestion() {

    isTextual = true;
    int bound = text_questions.size() - 1;
    std::string Q_str = text_questions[rand() % bound  + 0];
    text = split(Q_str,',',2,true);
    result = split(Q_str, ',', 3);
    //std::cout << text << " " << result;

    return *this;
}

//not needed
void Question::printQuestions() {
    std::cout << "\nQuestions:\n";
    for (auto x : text_questions) {
        std::cout << x << "\n";
    }
}




#endif