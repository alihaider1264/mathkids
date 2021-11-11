#ifndef _GRADE_
#define _GRADE_

class Grade {
	int grade_level;
public:
	Grade() : grade_level(1) {}
	Grade(const int& l) : grade_level(l) {}
	int getGradeLevel() { return grade_level; }
	int setGradeLevel(const int &l) { grade_level = l; }
	~Grade() {}
};

#endif