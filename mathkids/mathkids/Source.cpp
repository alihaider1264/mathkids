#include <iostream>
#include "GradeLevel.h"
#include "Score.h"
#include "Quiz.h"
#include <time.h>

void printQuestion(Question, int, bool);

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
		printQuestion(Q, myQuiz.getMode(), myQuiz.display_num_line());

		double result;
		std::cin >> result;


		if (myQuiz.checkQuestion(Q, result))
			std::cout << "\t\t\tCORRECT!\n";		
		else 
			std::cout << "\t\t\tWRONG!\n";

	}

	Score myScore = myQuiz.getScore();
	std::cout << "Score: " << myScore.getCorrect() << "/" << myScore.getTotal() << " " << myScore.getScore()*100 << "% \n";
}



void printQuestion(Question Q, int mode, bool display_num_line) {
	//print a number line
	if (Q.isText()) {
		std::cout << "Question: " << Q.getText() << ": ";
	}
	else {
		if (display_num_line) {
			std::cout << "Number line:\n";
			if (Q.getOperator() == '-' || Q.getOperator() == '+') {
				for (int i = -10; i <= 10; i++) {
					std::cout << i << " ";
				}
				std::cout << "\n";
			}
		}

		//print question
		if (mode == 0) {		//linear
			std::cout << "Solve:\n  " << Q.getOperand1() << " " << Q.getOperator() << " " << Q.getOperand2() << " = ";
		}
		else if (mode == 1) {	//stacked
			std::cout << "Solve:\n  " << Q.getOperand1() << "\n" << Q.getOperator() << " " << Q.getOperand2() << "\n-----\n";
		}
		else if (mode == 2) {	//reverse
			std::cout << "Solve:\n   = " << Q.getOperand1() << " " << Q.getOperator() << " " << Q.getOperand2() << "\r";
		}
	}


}
