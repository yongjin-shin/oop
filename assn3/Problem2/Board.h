#ifndef _BOARD_H_
#define  _BOARD_H_

#include <iostream>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"

class Board{
private:
  Piece* piece[3][4];
public:
  Board();
  virtual ~Board();
  Piece* get_piece(int x, int y){return piece[y][x];}
  void changePiece(Piece* new_p, int _x, int _y);
  void printBoard();
};

#endif
