#ifndef _QUESTION_
#define _QUESTION_

#include <string>
#include <vector>
#include <fstream>

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
            operand1(0), operand2(0), op(' '), isTextual(false), text(""), result(0){
        
		
            }
    Question(int op1, int op2, char oper, bool isText, std::string txt):
            operand1(op1), operand2(op2), op(oper), isTextual(isText), text(txt), result(0){
        //read textual questions
        std::string line;
        std::ifstream f;
        f.open("data/textual_questions.csv");
		if (f.is_open()) {
			while (f) {
				std::getline(f, line);
				text_questions.push_back(line);
			}
		}
		else {
			std::cout << "Couldn't open data/operators.dat file\n";
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
    std::string selectRandomTextQuestion();
    ~Question(){}

};


std::string Question::selectRandomTextQuestion() {

    return text_questions[rand() % text_questions.size() + 0];

}

#endif