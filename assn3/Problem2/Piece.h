#ifndef _PIECE_H_
#define  _PIECE_H_

#include <iostream>


//enum using for movement of piece
//enum will be used with Patter struct in the for loop
enum DIRECT { FOR=0, RIGHT, BACK, LEFT, FOR_RIGHT, BACK_RIGHT, BAKC_LEFT, FOR_LEFT=7 };

typedef struct p_array{
  int _x;
  int _y;
} Pattern;

class Board;

//pattern is able to represent the possible movement of each pieces
//isHeld can represnet the status that whether this piece is held or not
//isking represents this piece is whether a king or not
class Piece{
private:
  int pos_x;
  int pos_y;
  bool team;
  Pattern* pattern;
  int isHeld;
  int isking;

public:
	Piece(int pos_x, int pos_y, bool team, int _king);
  virtual ~Piece();
	virtual bool isPossibleMove(Board*, int _x, int _y) { return true; }
  virtual void printPossibleLocation(Board*){}
  virtual void printPieces(){}
  int get_x(){return pos_x;}
  int get_y(){return pos_y;}
  bool get_team(){return team;}
  int get_isHeld(){return isHeld;}
  void setPieces(Board* board, int _x, int _y);
  void teamChange();
  void heldChange(){isHeld = !isHeld;}
  Pattern* get_pattern(){return pattern;}
  int get_king(){return isking;}
};




#endif
