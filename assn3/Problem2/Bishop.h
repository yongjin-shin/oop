#ifndef _BISHOP_H_
#define  _BISHOP_H_

#include "Piece.h"

class Bishop : public Piece{
public:
  Bishop(int pos_x, int pos_y, bool team, int _king):Piece(pos_x, pos_y, team, _king){}
  ~Bishop(){}
  virtual bool isPossibleMove(Board* board, int _x, int _y);
  virtual void printPossibleLocation(Board* board);
  virtual void printPieces();

};


#endif
