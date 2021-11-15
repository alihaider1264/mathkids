#include <iostream>
#include "GradeLevel.h"
#include "Score.h"
#include "Quiz.h"
#include <time.h>

#define ops_array_size 4

int calculate(int, int, char);
int getNumber(GradeLevel);    //generate random operands
char getOperator(char[ops_array_size], GradeLevel); //generate random operator
int getMode();		//question can be printed in different ways i.e., modes
void printQuestion(int, int, char, int);

int main() {

	std::cout << "Welcome to Maths!\n";
	int grade, no_questions;
	std::cout << "Enter grade (1-5): ";
	std::cin >> grade;
	Quiz myQuiz = Quiz(grade);

	std::cout << "How many questions?: ";
	std::cin >> no_questions;

	Question Q;
	for (int i = 0; i < no_questions; i++) {
		Q = myQuiz.generateQuestion();

		int result;
		printQuestion(Q.operand1, Q.operand2, Q.op, myQuiz.getMode());
		std::cin >> result;


		if (myQuiz.checkQuestion(Q, result))
			std::cout << "\t\t\tCORRECT!\n";		
		else 
			std::cout << "\t\t\tWRONG!\n";

	}

	Score myScore = myQuiz.getScore();
	std::cout << "Score: " << myScore.getCorrect() << "/" << myScore.getTotal() << " " << myScore.getScore() << "\n";
}



void printQuestion(int operand1, int operand2, char op, int mode) {

	if (mode == 0) {		//linear
		std::cout << "Solve:\n  " << operand1 << " " << op << " " << operand2 << " = ";
	}
	else if (mode == 1) {	//stacked
		std::cout << "Solve:\n  " << operand1 << "\n" << op << " " << operand2 << "\n-----\n";
	}
	else if (mode == 2) {	//reverse
		std::cout << "Solve:\n  ? = " << operand1 << " " << op << " " << operand2 << "\r"; 
	}

}
