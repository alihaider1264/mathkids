#include <iostream>
#include "include/GradeLevel.h"
#include "include/Score.h"
#include "include/Quiz.h"
#include "include/Print.h"
#include <time.h>

void printQuestion(Question, int, bool);

int main() {

	std::cout << "Welcome to Maths!\n";
	int grade, no_questions;
	std::cout << "Enter grade (1-5): ";
	std::cin >> grade;
	Quiz myQuiz = Quiz(grade);
	Print myPage = Print();

	std::cout << "How many questions?: ";
	std::cin >> no_questions;

	Question Q;
	for (int i = 0; i < no_questions; i++) {
		Q = myQuiz.generateQuestion();
		//print on screen
		//myPage.printScreen(Q, myQuiz.getMode(), myQuiz.display_num_line());
		
		//print to file
		myPage.addQuestion(Q);

		/*
		double result;
		std::cin >> result;


		if (myQuiz.checkQuestion(Q, result))
			std::cout << "\t\t\tCORRECT!\n";		
		else 
			std::cout << "\t\t\tWRONG!\n";
		*/
	}
	myPage.printPage(myQuiz.getMode(), myQuiz.display_num_line());

	//Score myScore = myQuiz.getScore();
	//std::cout << "Score: " << myScore.getCorrect() << "/" << myScore.getTotal() << " " << myScore.getScore()*100 << "% \n";
}




