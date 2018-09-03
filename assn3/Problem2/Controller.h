#ifndef _CONTROLLER_H_
#define  _CONTROLLER_H_

#include "User.h"
#include "Board.h"
using namespace std;

class Controller{
private:
  Board* board;
  User* userA;
  User* userB;
  bool team;
  int cnt;
  int A_king_stay;
  int B_king_stay;
public:
  Controller();
  virtual ~Controller();
  int turn();
  void printStatus();
  bool isEnded();
};

#endif
