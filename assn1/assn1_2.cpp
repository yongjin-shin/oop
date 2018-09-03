#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string reverseNum(string num);
string removeZero(string num);
string compareNum(string num1, string num2);

int main(){
  int input1;
  int input2;
  string tmp1_converted;
  string tmp2_converted;

  ifstream infile;
  infile.open("input.txt");
  if(!infile.is_open()){
    cout<<"Cannot open input file."<<endl;
    return 100;
  }

  ofstream outfile;
  outfile.open("output.txt");
  if(!outfile.is_open()){
    cout<<"Cannot open output file."<<endl;
    return 200;
  }

  /*
  Convert each inputs into strings and again convert them into reverseNumber.
  After converting processes, the result will be proceeded with comparing two numbers.
  */
  while(infile >> input1 >> input2){
    string tmp1 = to_string(input1);
    string tmp2 = to_string(input2);

    tmp1_converted = reverseNum(tmp1);
    tmp2_converted = reverseNum(tmp2);
    string result = compareNum(tmp1_converted, tmp2_converted);
    outfile<< result << endl;
  }

  return 0;
}

//Stack each characters in the string in the opposite direction with using the size of string.
string reverseNum(string num){
  string _reversed;
  string _removed;
  int num_size = num.size();
  for(int i=num_size-1; 0<=i; i--){
    _reversed += num.at(i);
  }
  _removed = removeZero(_reversed);
  return _removed;
}

//Look up the first position of non-zero and remove all the strings by that position.
string removeZero(string num){
  string _removed;
  _removed = num.erase(0, num.find_first_not_of('0'));
  return _removed;
}

/*
First, check the size of each strings and if there is the one which is longer than the other, then return the longer one.
Second, if two strings have the same length, then compare them with 'compare' function and return the bigger one.
*/
string compareNum(string num1, string num2){
  int size_diff = num1.size() - num2.size();
  if(size_diff > 0)
    return num1;
  else if(size_diff < 0)
    return num2;
  else{
    if (num1.compare(num2) > 0)
      return num1;
    else
      return num2;
  }
}
