#include <iostream>
#include "Grade.h"
#include <time.h>


int calculate(int, int, char);

int main() {

	std::cout << "Welcome to Maths!\n";
	srand(time(NULL));
	bool more = true;
	while (more != false) {
		int operand1 = rand() % 10 + 0;
		int operand2 = rand() % 10 + 0;
		char op = '+';
		int result;
		char try_again;

		std::cout << "Solve:\n" << operand1 << " " << op << " " << operand2 << "=";
		std::cin >> result;

		if (result == calculate(operand1, operand2, op))
			std::cout << " CORRECT!\n";
		else
			std::cout << " WRONG!\n";

		std::cout << "Try again? (y/n): ";
		std::cin >> try_again;

		if (!try_again) more = false;
	}



}


int calculate(int op1, int op2, char op) {

	switch (op) {
	case '+': return op1 + op2;
	case '-': return op1 + op2;
	case '*': return op1 + op2;
	case '/': return op1 + op2;
	}

	return 0;
}
