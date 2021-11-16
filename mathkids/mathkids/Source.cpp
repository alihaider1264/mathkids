#include <iostream>
#include "GradeLevel.h"
#include "Score.h"
#include "Quiz.h"
#include <time.h>

void printQuestion(int, int, char, int, bool);

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
		printQuestion(Q.operand1, Q.operand2, Q.op, myQuiz.getMode(), myQuiz.diplay_number_line());
		std::cin >> result;


		if (myQuiz.checkQuestion(Q, result))
			std::cout << "\t\t\tCORRECT!\n";		
		else 
			std::cout << "\t\t\tWRONG!\n";

	}

	Score myScore = myQuiz.getScore();
	std::cout << "Score: " << myScore.getCorrect() << "/" << myScore.getTotal() << " " << myScore.getScore()*100 << "% \n";
}



void printQuestion(int operand1, int operand2, char op, int mode, bool display_num_line) {
	//print a number line
	if(display_num_line){
		std::cout<<"Number line:\n";
		if (op == '-' || op == '+'){
			for(int i=-10;i<=10;i++){
				std::cout << i << " ";
			}
			std::cout<<"\n";
		}
	}
	
	//print question
	if (mode == 0) {		//linear
		std::cout << "Solve:\n  " << operand1 << " " << op << " " << operand2 << " = ";
	}
	else if (mode == 1) {	//stacked
		std::cout << "Solve:\n  " << operand1 << "\n" << op << " " << operand2 << "\n-----\n";
	}
	else if (mode == 2) {	//reverse
		std::cout << "Solve:\n   = " << operand1 << " " << op << " " << operand2 << "\r"; 
	}

}
