#include <fstream>
#include "FirePok.h"
#include "GrassPok.h"
#include "WaterPok.h"

using namespace std;

int main(){
  ifstream infile;
  infile.open("input.txt");
  if(!infile.is_open()){
    cout << "Cannot open input file." << endl;
    return 100;
  }

  ofstream outfile;
  outfile.open("Output.txt");
  if(!outfile.is_open()){
    cout<<"Cannot open output file." <<endl;
    return 200;
  }

  int result = -1;
  int iteration = 0;
  Poketmon* first;
  string first_type;
  string first_atk;
  string first_df;
  string first_hp;

  Poketmon* second;
  string second_type;
  string second_atk;
  string second_df;
  string second_hp;

  infile >> iteration;
  for(int i = 0; i<iteration; i++){
    infile >> first_type >> first_atk >> first_df >> first_hp;
    infile >> second_type >> second_atk >> second_df >> second_hp;

    if(first_type.compare("Fire") ==0)
      first = new FirePok(first_type, stoi(first_atk), stoi(first_df), stoi(first_hp));
    else if (first_type.compare("Grass")==0)
      first = new GrassPok(first_type, stoi(first_atk), stoi(first_df), stoi(first_hp));
    else
      first = new WaterPok(first_type, stoi(first_atk), stoi(first_df), stoi(first_hp));

    if(second_type.compare("Fire") ==0)
      second = new FirePok(second_type, stoi(second_atk), stoi(second_df), stoi(second_hp));
    else if (second_type.compare("Grass")==0)
      second = new GrassPok(second_type, stoi(second_atk), stoi(second_df), stoi(second_hp));
    else
      second = new WaterPok(second_type, stoi(second_atk), stoi(second_df), stoi(second_hp));

    result = first->battle(second);

    if(result==2)
      outfile << 2 << endl;
    else if(result == 1)
      outfile << 1 << endl;
    else
      outfile << 0 << endl;
  }

    infile.close();
    outfile.close();
  return 0;
}
