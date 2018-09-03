#include "Piece.h"
#include "Board.h"

Piece::Piece(int pos_x, int pos_y, bool team, int _king) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->team = team;
  this->isking = _king;
  isHeld = 0;
  pattern = new Pattern[8];
  pattern[0]._x = 1;//forward
  pattern[0]._y = 0;

  pattern[1]._x = 0;//right
  pattern[1]._y = 1;

  pattern[2]._x = -1;//backward
  pattern[2]._y = 0;

  pattern[3]._x = 0;//left
  pattern[3]._y = -1;

  pattern[4]._x = 1;//forward_right
  pattern[4]._y = 1;

  pattern[5]._x = -1;//backward_right
  pattern[5]._y = 1;

  pattern[6]._x = -1;//backward_left
  pattern[6]._y = -1;

  pattern[7]._x = 1;//forward_left
  pattern[7]._y = -1;
}

Piece::~Piece(){}

//Only change the info of pieces' pos_x and pos_y
//the position in the board will be updated in the method "changePiece" in board class
//setPieces will be called in "movePiece" method in User class
void Piece::setPieces(Board* board, int _x, int _y){
  int old_x = pos_x;
  int old_y = pos_y;
  int new_x = pos_x = _x;
  int new_y = pos_y = _y;
  board->changePiece(this, new_x, new_y);
  if(isHeld != 1)
    board->changePiece(nullptr, old_x, old_y);
}

//change the team oppositetly. It will be used when the piece is held.
void Piece::teamChange(){
  team = !team;
}
