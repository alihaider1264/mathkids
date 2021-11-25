#ifndef _PRINT_
#define _PRINT_

#include "Question.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

class Print{
    std::vector<Question> page;

public:
    Print();
    bool addQuestion(Question);
    bool removeQuestion(int);
    bool isEmpty();
    int questionCount();
    bool printPage(const int&, bool);
    void printScreen(Question, int, bool);
    void printNumberLine(Question);
    std::string printMode(Question, int);
    ~Print(){}
};

Print::Print(){}

bool Print::addQuestion(Question Q){
    page.push_back(Q);
    return true;
}

bool Print::removeQuestion(int i){
    std::vector<Question>::iterator it = page.begin();
    page.erase(it);
    return true;
}

bool Print::isEmpty(){
    return page.size() == 0;
}

int Print::questionCount(){
    return page.size();
}

bool Print::printPage(const int &mode, bool num_line){

    std::cout << "Printing...";
    
	struct tm newtime;
	time_t now = time(0);
	localtime_r(&now, &newtime);
	std::ofstream f;
	f.open("page1.txt",std::ios_base::out);
	if(f.is_open()){
            //print date
            f  << newtime.tm_mon << "/" << newtime.tm_mday << "/" << 1900 + newtime.tm_year + "\n\n";

            //print number line
            f << "\n\nNumber line:\n";		
            for (int i = -10; i <= 10; i++) {
                f << i << " ";
            }
            f << "\n";
        

            for(Question q : page){
                if(!q.isText()){
                    f << printMode(q, rand() % 3 + 0); //make dynamic
                }
                else{
                    f << "\n\n" << q.getText() << " =";
                }
            }
	}
	f.close();
    return true;
}


void Print::printScreen(Question Q, int mode, bool display_num_line) {
	//print a number line
	if (Q.isText()) {
		std::cout << "Question: " << Q.getText() << ": ";
	}
	else {
		if (display_num_line) {
			printNumberLine(Q);
		}

		std::cout << printMode(Q, mode);
	}
}

void Print::printNumberLine(Question Q){
    std::cout << "Number line:\n";
    if (Q.getOperator() == '-' || Q.getOperator() == '+') {
        for (int i = -10; i <= 10; i++) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

std::string Print::printMode(Question Q, int mode){
    //print question
		if (mode == 0) {		//linear
			return "\n\n" + std::to_string(Q.getOperand1()) + " " + Q.getOperator() + " " + std::to_string(Q.getOperand2()) + " = ";
		}
		else if (mode == 1) {	//stacked
			return "\n\n\t" + std::to_string(Q.getOperand1()) + "\n" + Q.getOperator() + "\t" + std::to_string(Q.getOperand2()) + "\n---------\n";
		}
		else if (mode == 2) {	//reverse
			return  "\n\n   = " + std::to_string(Q.getOperand1()) + " " + Q.getOperator() + " " + std::to_string(Q.getOperand2()) + "\r";
		}
    return "";
}

#endif