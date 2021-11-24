#ifndef _QUIZ_
#define _QUIZ_

#include <iostream>
#include <fstream>
#include "GradeLevel.h"
#include "Score.h"
#include "Question.h"
#include <ctime>
#include <string>
#include <vector>
#include "Split.h"



class Quiz {
	std::vector<char> ops;
	GradeLevel level;
	Score myScore;
	Question Q;
	int question_display_modes;
	bool display_number_line;
public:
	Quiz(const int &grade) {
		srand(time(NULL));
		std::string line;
		std::vector<std::string> split_line;
		std::ifstream f;
		
		//read config.json file
		f.open("config.dat");
		if (f.is_open()) {
			std::getline(f, line);
			question_display_modes = split(line, '=', 2);

			std::getline(f, line);
			display_number_line = split(line, '=', 2);
		}
		else {
			std::cout << "Couldn't open config.dat file\n";
		}

		f.close();
		
		//populate operators from operators.dat
		f.open("_data/operators.dat");
		if (f.is_open()) {
			while (f) {
				std::getline(f, line);
				ops.push_back((char)line[0]);
			}
		}
		else {
			std::cout << "Couldn't open _data/operators.dat file\n";
		}
		//
		f.close();
		
		level = GradeLevel(grade);
		myScore = Score();
	}

	int calculate();		//solve the problem and get result
	int getNumber();		//generate random operand value
	char getOperator();		//pick an operator randomly from available operators
	int getMode();			//pick a question display mode randomly
	Question generateQuestion();
	bool checkQuestion(Question, double);
	Score getScore();
	bool display_num_line();
	~Quiz() {}
};

int Quiz::calculate() {

	switch (Q.getOperator()) {
	case '+': return Q.getOperand1() + Q.getOperand2();
	case '-': return Q.getOperand1() - Q.getOperand2();
	case '*': return Q.getOperand1() * Q.getOperand2();
	case '/': return Q.getOperand1() / Q.getOperand2();
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

	if (level.getGradeLevel() == 1 || level.getGradeLevel() == 2) bound = 2;
	else if (level.getGradeLevel() == 3) bound = 4;

	return ops[rand() % bound + 0];
}

int Quiz::getMode() {
	return rand() % question_display_modes + 0;
}


Question Quiz::generateQuestion() {
	int random_num = rand() % 2 + 0;

	switch (random_num) {
		
	case 0:
		//numerical
		Q = Question(getNumber(), getNumber(), getOperator(), false, "");
		Q.setResult(calculate());
		break;

	case 1:
		//textual
		Q = Question(0, 0, ' ', true, "");
		Q = Q.selectRandomTextQuestion();
	}
	return Q;
}

bool Quiz::checkQuestion(Question Q, double result) {

	if (result == Q.getResult()) {
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
	struct tm newtime;
	time_t now = time(0);
	localtime_r(&now, &newtime);
	std::ofstream f;
	f.open("_data/results.csv",std::ios_base::app);
	if(f.is_open()){
		f << newtime.tm_mon << "/" << newtime.tm_mday << "/" << 1900 + newtime.tm_year << " "
		<< newtime.tm_hour << ":" << newtime.tm_min << "," << std::to_string(myScore.getCorrect())
		+ "," + std::to_string(myScore.getTotal())+"\n";
	}
	f.close();
	return myScore;
}

bool Quiz::display_num_line(){
	return (int)display_number_line == 1;
}


#endif
