#include <iostream>
#include <string>
#include "Studentinfo.h"


//StudentInfo::StudentInfo() {}

StudentInfo::StudentInfo(std::string name, std::string department, int* PreCourses, int* Courses) {
  this->name = name;
  this->department = department;
  this->PreCourses = PreCourses;
  this->courses = Courses;
}

StudentInfo::~StudentInfo() {
	//destructor
}

bool StudentInfo::Register(CourseInfo** courselist, int AcademicNum){
  bool tmp = 0;
  bool pre_check = 0;
  pre_check=this->CheckPrerequisite(courselist, AcademicNum);
  if(pre_check == 0){
    //check class time
	//after checking class time, if is okay then put it in the courses array.
	  if (courses[0] == 0) {
		  courses[1] = AcademicNum;
		  courses[1]++;
	  }
	  else {
		  courses[courses[0]] = AcademicNum;
		  courses[1]++;
	  }
	  tmp = 1;
  }
  return tmp;
}

bool StudentInfo::CheckPrerequisite(CourseInfo** courselist, int index){
  bool result=0;
  int index_req = 0;
  int course = 0;
  //get the size of prerequisite of 'index'
  //first, find what course index is
  for(course = 0; course<course_num; course++){
    if(courselist[course]->getAcademicNum() == index)
      break;
    }
  //secondly, get the size!
  index_req = courselist[course]->getprerequisite()[0];
  std::cout << "index_req is " << index_req << std::endl;//====

  //if there is no prerequisite, then return true
  if(index_req == 0)
    return result = 1;

  //binary search for CS students
  if(this->name.compare("CS") == 0){
	  int pre_count = 0;//for checking how many prerequisite which the student has taken.
	  //binary search
	  for (int i = 0; i <= index_req; i++) {
		  int target = courselist[course]->getprerequisite()[i];
		  int initial = 1;
		  int final = initial + PreCourses[0];
		  int mid;
		  int location = -1;

		  while (initial <= final)
		  {
			  mid = (initial + final) / 2;
			  if (PreCourses[mid] == target)
			  {
				  location = mid;
				  break;
			  }
			  if (target<PreCourses[mid])
				  final = mid - 1;
			  if (target>PreCourses[mid])
				  initial = mid + 1;
		  }
		  //if there is a matching between two prerequisite, plus count!
		  if (location != -1)
			  pre_count++;
	  }
	  //if the number of the course's prerequiste is same with count, the student take all the courses
	  if (pre_count == index_req)
		  result = 1;
  }

  //linear search for MATH students
  else{
    int lin_check=1;//For looping course's prerequisite
    int _lin_check=1;//For looping student's prerequisite
    int pre_count=0;//count how many courses student has been taking
    for(lin_check=1; lin_check<=index_req; lin_check++){
      for(_lin_check = 1; _lin_check<=PreCourses[0]; _lin_check++){
        if(courselist[course]->getprerequisite()[lin_check] == PreCourses[_lin_check]){
          pre_count++;//if there is same prerequiste btw course and studnet, plus count!
          break;
        }
      }
    }

    //the loop breaks in the middle only if students take all the prerequisite.
	//if the number of the course's prerequiste is same with count, the student take all the courses
    if(pre_count == index_req)
      result=1;
  }
    return result;
}

void StudentInfo::Drop(int AcademicNum){

}

std::string StudentInfo::Print(){
	std::string tmp = name;
	for (int i = 1; i <= courses[0]; i++) {
		tmp += " "+std::to_string(courses[i]);
	}
  return tmp;
}

std::string StudentInfo::getname(){
  return this->name;
}

int* StudentInfo::getcourses(){
  return this->courses;
}
