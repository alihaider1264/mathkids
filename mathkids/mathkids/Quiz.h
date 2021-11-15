#ifndef _QUIZ_
#define _QUIZ_

#include <iostream>
#include <fstream>
#include "GradeLevel.h"
#include "Score.h"
#include <time.h>
#include <string>
#include <vector>

struct Question {
	int operand1;
	int operand2;
	int op;
};

class Quiz {
	std::vector<char> ops;
	char op;
	int operand1, operand2;
	GradeLevel level;
	Score myScore;
public:
	Quiz(const int &grade) {
		srand(time(NULL));
		
		//populate operators from operators.dat
		std::string line;
		std::ifstream f;
		f.open("data/operators.dat");
		if (f.is_open()) {
			while (f) {
				std::getline(f, line);
				ops.push_back((char)line[0]);
			}
		}
		else {
			std::cout << "Couldn't open data/operators.dat file\n";
		}
		//

		op = ' '; operand1 = 0; operand2 = 0;
		level = GradeLevel(grade);
		myScore = Score();
	}

	int calculate();		//solve the problem and get result
	int getNumber();		//generate random operand value
	char getOperator();		//pick an operator randomly from available operators
	int getMode();			//pick a question display mode randomly
	Question generateQuestion();
	bool checkQuestion(Question, int);
	Score getScore();
	~Quiz() {}
};

int Quiz::calculate() {

	switch (op) {
	case '+': return operand1 + operand2;
	case '-': return operand1 - operand2;
	case '*': return operand1 * operand2;
	case '/': return operand1 / operand2;
	}

	return 0;
}

int Quiz::getNumber() {
	if (level.getGradeLevel() == 1)
		return rand() % 10 + 0;
	else if (level.getGradeLevel() == 2)
		return rand() % 100 + 0;

	return rand() % 10 + 0;
}

char Quiz::getOperator() {
	int bound = ops.size();

	if (level.getGradeLevel() == 1 || level.getGradeLevel() == 2) bound = 3;
	else if (level.getGradeLevel() == 3) bound = 4;

	return ops[rand() % bound + 0];
}

int Quiz::getMode() {
	return rand() % 3 + 0;
}


Question Quiz::generateQuestion() {
	Question Q;

	operand1 = getNumber();
	op = getOperator();
	operand2 = getNumber();

	Q.operand1 = operand1;
	Q.operand2 = operand2;
	Q.op = op;
	
	return Q;
}

bool Quiz::checkQuestion(Question Q, int result) {

	if (result == calculate()) {
		myScore.inc_correct();
		myScore.inc_total();
		return true;
	}
	else {
		myScore.inc_total();
		return false;
	}
}

Score Quiz::getScore() {
	return myScore;
}



#endif
