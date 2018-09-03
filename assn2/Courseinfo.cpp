#include <iostream>
#include <string>
#include "Courseinfo.h"

CourseInfo::CourseInfo(int AcademicNum, std::string classname, ClassTime* times, int* prerequisite){
	this->AcademicNum = AcademicNum;
	this->classname = classname;
	this->times = times;
	this->prerequisite = prerequisite;
}

CourseInfo::~CourseInfo(){
	//Destructor
}

int CourseInfo::getAcademicNum(){
  return AcademicNum;
}

int* CourseInfo::getprerequisite(){
  return prerequisite;
}

ClassTime* CourseInfo::gettimes(){
	return times;
}
