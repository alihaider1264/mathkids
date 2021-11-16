#ifndef _QUIZ_
#define _QUIZ_

#include <iostream>
#include <fstream>
#include "GradeLevel.h"
#include "Score.h"
#include "Question.h"
#include <time.h>
#include <string>
#include <vector>
//#include <boost/algorithm/split.hpp>


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
		display_number_line=1;
		/*
		//read .config file
		f.open(".config");
		if (f.is_open()) {
			std::getline(f, line);
			boost::split(split_line, line, boost::is_any_of("="));
			question_display_modes = split_line[1];

			std::getline(f, line);
			boost::split(split_line, line, boost::is_any_of(","));
			display_number_line = split_line[1];
			}
		}
		else {
			std::cout << "Couldn't open data/operators.dat file\n";
		}

		f.close();
		*/
		//populate operators from operators.dat
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
		f.close();
		
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
	bool diplay_number_line();
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
	return rand() % 3 + 0;
}


Question Quiz::generateQuestion() {

	//randomize numerical and textual questions
	//numerical
	Q = Question(getNumber(), getNumber(), getOperator(), false, "");
	Q.setResult(calculate());


	//split question text here
	//textual
	Q = Question(0,0,' ',true,Q.selectRandomTextQuestion());
	Q.setResult(0); //set result after split

	return Q;
}

bool Quiz::checkQuestion(Question Q, int result) {

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
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::ofstream f;
	f.open("data/results.csv",std::ios_base::app);
	if(f.is_open()){
		f << ltm->tm_mon << "/" << ltm->tm_mday << "/" << 1900 + ltm->tm_year << " " 
		<< ltm->tm_hour << ":" << ltm->tm_min << "," << std::to_string(myScore.getCorrect()) 
		+ "," + std::to_string(myScore.getTotal())+"\n";
	}
	f.close();
	return myScore;
}

bool Quiz::diplay_number_line(){
	return (int)display_number_line == 1;
}


#endif
