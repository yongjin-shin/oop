#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum SRPSL {
  SCISSORS=1, ROCK, PAPER, LIZARD, SPOCK
};

enum SRPSL ChooseAmongSRPSL (int index);
bool IsWinner(enum SRPSL A, enum SRPSL B);

int main(){
  int num;

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

  while(infile >> num){
    int* plyrs = new int[num];
    enum SRPSL* sprsl = new enum SRPSL[num];
    int win_count = 0;
    int* winners = new int[num];

    //Put the index of plyers in the array followed by SPRSL.
    for(int i=0; i<num; i++){
      infile >> plyrs[i];
      sprsl[i] = ChooseAmongSRPSL(plyrs[i]);
    }

    /* when a player lose the game, then return false and vice versa.
    We only need to know the player who loses at least once
    and gather all the winners in the array with couting the number of winners.
    If the number will be same with that of players when they put the same things. In the other hand, if there will be a draw case, then there will be no winner in the array.*/

    for(int i=0; i<num; i++){
      int j=0;
      for(j=0; j<num; j++){
        if(!IsWinner(sprsl[i], sprsl[j]))//Get out of for loop if plyrs loses game at least once with taking false value from the function.
          break;
      }
      if(j == num){//if the player either wins or draws all the game, then we save the player.
        winners[win_count] = plyrs[i];
        win_count++;
      }
    }

    if(win_count == num)//If the number of winners is exactly same with that of all the players, then the game can be considered as a draw case.
      outfile << 0 << endl;
    else if(win_count == 0) //If the number is 0, then there is no one to win.
      outfile << 0 << endl;
    else{
      for(int i=0; i<win_count; i++){
        outfile << winners[i] << " ";
      }
      outfile << endl;
    }

    delete[] sprsl;
    delete[] plyrs;
  }

  return 0;
}

enum SRPSL ChooseAmongSRPSL(int index){
  enum SRPSL result;

  switch (index) {
    case 1:
      result = SCISSORS;
      break;
    case 2:
      result = ROCK;
      break;
    case 3:
      result = PAPER;
      break;
    case 4:
      result = LIZARD;
      break;
    case 5:
      result = SPOCK;
      break;
    case 6://make a random number among 1 and 2
      srand((unsigned int)time(NULL));
      result = SRPSL(rand()% 2+1);
      break;
    case 7://make a random number from 3 to 5
      srand((unsigned int)time(NULL));
      result = SRPSL(rand()% 3+3);
      break;
    case 8://make a random number from 1 to 3
      srand((unsigned int)time(NULL));
      result = SRPSL(rand()% 3+1);
      break;
    case 9://make a random number from 1 to 5
      srand((unsigned int)time(NULL));
      result = SRPSL(rand()%5+1);
      break;
  }
  return result;
}

bool IsWinner(enum SRPSL A, enum SRPSL B){
  bool result = true;

  switch (A) {//A loses only if Return 'false'
    case SCISSORS:
      if(B==ROCK || B==SPOCK)
        result = false;
        break;
    case ROCK:
      if(B==PAPER || B==SPOCK)
        result = false;
        break;
    case PAPER:
      if(B==SCISSORS || B==LIZARD)
        result = false;
        break;
    case LIZARD:
      if(B==SCISSORS || B==ROCK)
        result = false;
        break;
    case SPOCK:
      if(B==PAPER || B==LIZARD)
        result = false;
        break;
  }

  return result;
}
