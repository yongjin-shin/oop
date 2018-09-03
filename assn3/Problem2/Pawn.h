#ifndef _PAWN_H_
#define  _PAWN_H_

#include "Piece.h"

class Pawn : public Piece{
public:
  Pawn(int pos_x, int pos_y, bool team, int _king):Piece(pos_x, pos_y, team, _king){}
  virtual bool isPossibleMove(Board* board, int _x, int _y);
  virtual void printPossibleLocation(Board* board);
  virtual void printPieces();
};

#endif