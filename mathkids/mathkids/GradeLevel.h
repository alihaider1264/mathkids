#ifndef _GRADE_
#define _GRADE_

class GradeLevel {
	int grade_level;
public:
	GradeLevel() : grade_level(1) {}
	GradeLevel(const int& l) : grade_level(l) {}
	int getGradeLevel() { return grade_level; }
	void setGradeLevel(const int &l) { grade_level = l; }
	~GradeLevel() {}
};

#endif