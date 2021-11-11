#include <iostream>
#include "Grade.h"
#include <time.h>

#define ops_array_size 4

int calculate(int, int, char);
int getNumber();
char getOperator(char[ops_array_size]);

int main() {

	std::cout << "Welcome to Maths!\n";
	srand(time(NULL));
	bool more = true;
	char ops[ops_array_size] = { '+', '-', '*', '/' }, op;
	int operand1, operand2;

	while (more != false) {

		int result;
		char try_again;
		operand1 = getNumber();
		operand2 = getNumber();
		char op = getOperator(ops);

		std::cout << "Solve:\n" << operand1 << " " << op << " " << operand2 << "=";
		std::cin >> result;

		if (result == calculate(operand1, operand2, op))
			std::cout << " CORRECT!\n";
		else
			std::cout << " WRONG!\n";

		std::cout << "Try again? (y/n): ";
		std::cin >> try_again;

		if (try_again == 'n' || try_again == 'N')
			more = false;
	}



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

int getNumber() {
	return rand() % 10 + 0;
}

char getOperator(char ops[ops_array_size]) {
	int bound = ops_array_size - 1;
	return ops[rand() % bound + 0];
}