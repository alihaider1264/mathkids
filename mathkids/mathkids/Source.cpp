#include <iostream>
#include "include/GradeLevel.h"
#include "include/Score.h"
#include "include/Quiz.h"
#include "include/Print.h"
#include <time.h>

void printQuestion(Question, int, bool);

int main(int argc, char *argv[]) {

	std::cout << "Welcome to Maths!\n";
	int grade, no_questions;
	std::cout << "Enter grade (1-5): ";
	std::cin >> grade;
	Quiz myQuiz = Quiz(grade);
	Print myPrint = Print();
	
	std::cout << "How many questions?: ";
	std::cin >> no_questions;

	std::string screen = argv[0];
	std::cout << "screen:" << argv[0];

	

	Question Q;
	if (screen == std::to_string(1)){
		for (int i = 0; i < no_questions; i++) {
			Q = myQuiz.generateQuestion(true);
			//print on screen
			myPrint.printScreen(Q, myQuiz.getMode(), myQuiz.display_num_line());

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
	else{

		for (int i = 0; i < no_questions; i++) {
			//generate question
			Q = myQuiz.generateQuestion(true);
			
			//add to page vector
			myPrint.addQuestion(Q);

		}
		//print questions to file
		myPrint.printPage(myQuiz.getMode(), myQuiz.display_num_line(), 3); //3 = no of colums to be printed on each page

	}
}




