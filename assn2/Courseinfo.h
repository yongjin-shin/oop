#include <iostream>
#include <string>
#include "Classtime.h"


class CourseInfo {
public:
	CourseInfo(int AcademicNum, std::string classname, ClassTime* times, int* prerequisite);
	~CourseInfo();
	int getAcademicNum();
	int* getprerequisite();
	ClassTime* gettimes();
private:
	int AcademicNum;
	std::string classname;
	ClassTime* times;
	int* prerequisite;
};
