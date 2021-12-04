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
    bool printPage(const int&, bool, int);
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

bool Print::printPage(const int &mode, bool num_line, int cols){

    std::cout << "Printing...";
    
	struct tm newtime;
	time_t now = time(0);
	localtime_r(&now, &newtime);
	std::ofstream f;
	f.open(std::to_string(time(0))+".html",std::ios_base::out);
	if(f.is_open()){
            //print date
            f << "<html><head><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />";
            f << "<link rel=\"stylesheet\" type=\"text/css\" href=\"site.css\"></head><body>";
            f << "<table id=\"main-table\"><tr><td colspan=" + std::to_string(cols) + ">";
            f << std::to_string(1 + (int)newtime.tm_mon) << "/" << newtime.tm_mday << "/" << std::to_string(1900 + (int)newtime.tm_year) + "\n\n";
            f << "</tr></td>";
            f << "<tr><td colspan=" + std::to_string(cols) + ">";
            //print number line
            f << "<table><tr>Number line:</tr><tr>";		
            for (int i = -10; i <= 10; i++) {
                f << "<td>" << i << "</td>";
                }
            f << "</tr></table>";
            f << "</tr></td>";
           
            std::vector<Question>::iterator it = page.begin();
            for(;it != page.end(); it++){
                f << "<tr>";
                for(int i=0;i<cols;i++){
            
                    f << "<td>";
                    if(!it->isText()){
                        f << printMode(*it, rand() % 3 + 0); //make dynamic
                    }
                    else{
                        f << it->getText() << " =";
                    }
                    f << "</td>";

                    it++;
                }
                f << "</tr>";
                
                /* f << "<td>";
                if(!it->isText()){
                    f << printMode(*it, rand() % 3 + 0); //make dynamic
                }
                else{
                    f << it->getText() << " =";
                }
                 f << "</td></tr>";
                 */

            }
            f << "</table></body></html>";
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
			return "<table><tr><td id=\"simple_question\">" + std::to_string(Q.getOperand1()) + " " + Q.getOperator() + " " + std::to_string(Q.getOperand2()) + " = </td></tr></table>";
		}
		else if (mode == 1) {	//stacked
			return "<table style=\"border-bottom:2px solid black\"><tr><td></td><td>" + std::to_string(Q.getOperand1()) + "</td></tr><tr><td id=\"stacked_question\">" + Q.getOperator() + "</td><td id=\"stacked_question\">" + std::to_string(Q.getOperand2()) + "</td></tr><tr><td id=\"stacked_question\"></td><td id=\"stacked_question\"></td></tr></table>";
		}
		else if (mode == 2) {	//reverse
			return  "<table><tr><td id=\"text_question\">&nbsp;&nbsp;&nbsp;&nbsp;   = " + std::to_string(Q.getOperand1()) + " " + Q.getOperator() + " " + std::to_string(Q.getOperand2()) + "</td></tr></table>";
		}
    return "";
}

#endif