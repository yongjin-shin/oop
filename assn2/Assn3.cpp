#include<iostream>
#include<fstream>
#include<string>
#include"Studentinfo.h"

using namespace std;
using namespace Name;


/* ===Notice===
the first element of precourse/course array is
the size of each of them.
*/

int main(){
  const int child_num = 4;

  int* choi_class = new int[class_num];
  for(int i = 0; i<10; i++)
    choi_class[i] = 0;
  int choi_pre_[] = {1, 101};
  int* choi_pre = new int[2];
  memcpy(choi_pre, choi_pre_, 2*sizeof(int));

  int* lim_class = new int[class_num];
  for(int i = 0; i<10; i++)
    lim_class[i] = 0;
  int* lim_pre = new int[2];//{1,101};

  int* sim_class = new int[class_num];
  for(int i = 0; i<10; i++)
    sim_class[i] = 0;
  int* sim_pre = new int[9];//{8, 101, 211, 232, 233, 261, 273, 290, 291};

  int* cho_class = new int[class_num];
  for(int i = 0; i<10; i++)
    cho_class[i] = 0;
  int* cho_pre = new int[11];//{10, 101, 211, 233, 273, 312, 321, 332, 331, 341, 353};

  //allocate students in the arry named by "child"
  StudentInfo child[4]={StudentInfo("Choi", "MATH", choi_pre, choi_class), StudentInfo("Lim", "MATH", lim_pre, lim_class), StudentInfo("Sim", "CS", sim_pre, sim_class), StudentInfo("Cho", "CS", cho_pre, cho_class)};

  ClassTime cs273[3] = {ClassTime(Mon, 1100, 1215), ClassTime(Wed, 1100, 1215), ClassTime(Fri, 1400, 1630)};
  int _cs273[] = {0};//the first element is the size of array

  ClassTime cs514[3] = {ClassTime(Mon, 1100, 1215), ClassTime(Wed, 1100, 1215), ClassTime(Fri, 1400, 1630)};
  int _cs514[] = {1, 261};

  CourseInfo* c_273 = new CourseInfo(273, "Digital System Design", cs273, _cs273);
  CourseInfo* c_514 = new CourseInfo(514, "Patter Recognition", cs514, _cs514);

  CourseInfo* courselist[course_num] = { c_273, c_514 };

  cout << "check is " << child[0].CheckPrerequisite(courselist, 514) << endl;


  int oper;
  string _name;
  int* _input_c = new int[class_num];
  int class_count = 0;//the number of classes which a student wish to either resister or drop

  //Save input text into "input" variable
  const string input = "1 Choi 273\n1 Lim 261 353 321 233 232\n1 Sim 311 442 331 421 423\n1 Cho 504 507 515 514 518 700 702 703\n2 Sim 311 442\n2 Cho 504\n0\n1 Cho 504\n0\n";
  const char nl = '\n';
  const char ws = ' ';
  string copy_input = input;//copy 'input' into 'copy_input'

  int _times = 1;//---------

  //parsing process of input text
  //First, find the postion of 'new line(nl)' and upto this postion, get the string of the whole line
  //And save it into '_line' and then leave input text without '_line'
  //Second, find the position of every single 'white space(ws)' and extract each string
  //from the process of parsing 'white space' we can get 1)operation code[1, 2, 0], 2)student name, 3)coure list to register or to drop
  while(copy_input.find(nl)!=string::npos){
    string _line = copy_input.substr(0, copy_input.find(nl)+1);
    copy_input = copy_input.erase(0, copy_input.find(nl)+1);
    oper = stoi(_line.substr(0, _line.find(ws)));//get the operation code from the line
    _line = _line.erase(0, _line.find(ws)+1);
	_name = _line.substr(0, _line.find(ws));//get the student name from the line
	_line = _line.erase(0, _line.find(ws) + 1);

	//if operation code is 0, then print out whole students' courses resistered
	if (oper == 0) {
		for (int j = 0; j < child_num; j++) {
			child[j].Print();
			cout << endl;
		}
		continue;
	}

	//otherwise, there will be either a register process or a drop process
	//before proceeding each process, get courses from the input
	while (1) {
		_input_c[class_count] = stoi(_line.substr(0, _line.find(ws)));
		if (_line.find(nl) == 3)//the last course in the input always has '\n' positioned at 3
			break;
		_line = _line.erase(0, _line.find(ws) + 1);
		class_count++;
	}

	//With using the name from the input line
	//check the correction between the array of students and the name
	//Through this process, we can find who will our target student.
	int child_id = 0;
	for (child_id = 0; child_id < child_num; child_id++) {
		if (_name.compare(child[child_id].getname()) == 0)
			break;
	}
	switch (oper)
	{
	case 1://Register process
		for (int i = 0; i < class_count; i++)
			//child[child_id].Register(courselist ,_input_c[i]);
		break;
	case 2://Drop process
		break;
	default:
		break;
	}

	class_count = 0;
  }
  return 0;
}
