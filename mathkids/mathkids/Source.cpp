#include <iostream>
#include "GradeLevel.h"
#include "Score.h"
#include <time.h>

#define ops_array_size 4

int calculate(int, int, char);
int getNumber(GradeLevel);    //generate random operands
char getOperator(char[ops_array_size], GradeLevel); //generate random operator
int getMode();		//question can be printed in different ways i.e., modes
void printQuestion(int, int, char, int);

int main() {

	std::cout << "Welcome to Maths!\n";
	srand(time(NULL));
	char ops[ops_array_size] = { '+', '-', '*', '/' };
	char op;
	int operand1, operand2;
	GradeLevel level = GradeLevel();
	Score myScore = Score();

	int grade, no_questions;
	std::cout << "Enter grade: ";
	std::cin >> grade;
	level.setGradeLevel(grade);

	std::cout << "How many questions?: ";
	std::cin >> no_questions;

	for (int i=0;i<no_questions;i++){

		int result;
		operand1 = getNumber(level);
		char op = getOperator(ops, level);
		operand2 = getNumber(level);
		
		printQuestion(operand1, operand2, op, getMode());
		std::cin >> result;

		if (result == calculate(operand1, operand2, op)){
			std::cout << "\t\t\tCORRECT!\n";
			myScore.inc_correct();
			}
		else{
			std::cout << "\t\t\tWRONG!\n";
			}
		
		myScore.inc_total();
	}

	std::cout << "Score: " << myScore.getCorrect() << "/" << myScore.getTotal() << " " << myScore.getScore() << "\n";
}


int calculate(int op1, int op2, char op) {

	switch (op) {
	case '+': return op1 + op2;
	case '-': return op1 - op2;
	case '*': return op1 * op2;
	case '/': return op1 / op2;
	}

	return 0;
}

int getNumber(GradeLevel level) {
	if(level.getGradeLevel() == 1 )
		return rand() % 10 + 0;
	else if (level.getGradeLevel() == 2)
		return rand() % 100 + 0;
	
	return rand() % 10 + 0;
}

char getOperator(char ops[ops_array_size], GradeLevel level) {
	int bound = ops_array_size;

	if (level.getGradeLevel() == 1 || level.getGradeLevel() == 2) bound = ops_array_size - 2;
	else if (level.getGradeLevel() == 3) bound = ops_array_size - 1;

	return ops[rand() % bound + 0];
}

int getMode() {
	return rand() % 3 + 0;
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
