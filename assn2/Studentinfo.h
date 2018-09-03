#include<iostream>
#include<string>
#define course_num 2
#define class_num 16
#include"Courseinfo.h"


class StudentInfo {
public:
	StudentInfo(std::string name, std::string department, int* PreCourses, int* Courses);
	//StudentInfo();
	~StudentInfo();
	bool Register(CourseInfo** courselist, int AcademicNum);
	bool CheckPrerequisite(CourseInfo** courselist, int index);
	void Drop(int AcademicNum);
	std::string Print();
	std::string getname();
	int* getcourses();
private:
	std::string name;
	std::string department;
	int* PreCourses;
	int* courses;
};
