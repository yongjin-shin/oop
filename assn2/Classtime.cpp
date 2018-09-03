#include<iostream>
#include "Classtime.h"

ClassTime::ClassTime(Name::Day classtime_day, int classtime_start, int classtime_end){
	this->classtime_day = classtime_day;
	this->classtime_start = classtime_start;
	this->classtime_end = classtime_end;
}

ClassTime::~ClassTime(){
	//Destructor
}

Name::Day ClassTime::getclasstime_day(){
  return classtime_day;
}

int ClassTime::getclasstime_start(){
  return classtime_start;
}

int ClassTime::getclasstime_end(){
  return classtime_end;
}
