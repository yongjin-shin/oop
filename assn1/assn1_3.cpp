#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ofstream outfile;
struct DecimalConversion{
  int Integer;
  float Fraction;
  string ConvertedNumber;
};

void decompose(float num, struct DecimalConversion& dc);
void convert_integer(int n, struct DecimalConversion& dc);
void convert_fraction(int n, struct DecimalConversion& dc);
void convert (float num, int n, struct DecimalConversion& dc);
void print_converted_number(struct DecimalConversion& dc);

int main(){
  DecimalConversion dc;
  float input;
  int base;

  ifstream infile;
  infile.open("input.txt");
  if(!infile.is_open()){
    cout<<"Cannot open input file."<<endl;
    return 100;
  }

  outfile.open("output.txt");
  if(!outfile.is_open()){
    cout<<"Cannot open output file."<<endl;
  }

  while(infile >> base >> input){
    try{
      convert(input, base, dc);
      print_converted_number(dc);
    }catch (const char*msg){ //catch 'throw' from 'convert_fraction' function in 'convert' function
      outfile << msg << endl;
    }
  }
  return 0;
}

//With using static cast, convert input number into integer followed by getting fraction from the straction from input to integer.
void decompose(float num, struct DecimalConversion& dc){
  dc.Integer = static_cast<int>(num);
  dc.Fraction = num-dc.Integer;
}

//First, get integers beased 'n' with using mod n.
void convert_integer(int n, struct DecimalConversion& dc){
  int integer = dc.Integer;
  string tmp;
  string tmp_ConvertedNum;
  while(integer){
    tmp += to_string(integer%n);
    integer = integer/n;
  }

  //Stack each characters in the opposite direction with using the size of strings
  int size_tmp = tmp.size();
  for(int i=size_tmp-1; 0<=i; i--){
    tmp_ConvertedNum += tmp.at(i);
  }
  dc.ConvertedNumber = tmp_ConvertedNum;
}

/*
If the fraction is 0 then, return '.0'
Otherwise, return fraction base 'n'
While getting converted fraction, a counting is proceeded each iterations to judge if the fraction is over 10 digits.
*/
void convert_fraction(int n, struct DecimalConversion& dc){
  float fraction = dc.Fraction;
  string tmp_;
  int count=0;
  if(fraction == 0)
    tmp_ = to_string(0);
  while(fraction>0){
    int num = static_cast<int>(fraction*n);
    fraction = fraction*n;
    if(num>=1){
      tmp_ += to_string(num);
      fraction -= num;
    }
    else{
      tmp_ += to_string(0);
    }
    count++;

    //if count reach over 10, then throw 'infinite number'
    if(count>10){
      throw "infinite number";
    }
  }
  dc.ConvertedNumber += ".";
  dc.ConvertedNumber += tmp_;
}

//in the convert function, include every functions of converting number
void convert(float num, int n, struct DecimalConversion& dc){
    decompose(num, dc);
    convert_integer(n, dc);
    convert_fraction(n, dc);
}

//print out converted number in the out file
void print_converted_number(struct DecimalConversion& dc){
    outfile << dc.ConvertedNumber << endl;
}
