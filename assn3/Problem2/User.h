#ifndef _USER_H_
#define  _USER_H_

#include "Board.h"

class User{
private:
  bool team;
  Piece* OnboardPiece[7];
  Piece* HeldPiece[7];
public:
  User(bool team, Board* board);
  virtual ~User();
  void update_Piece(Board* board);
  void printUser();
  void movePieces(Piece* on_piece, Board* board, int _x, int _y);
  void HeldtoOnboard(int held, Board* board, int _x, int _y);
  Piece** get_onpiece(){return OnboardPiece;}
  Piece** get_heldpiece(){return HeldPiece;}
};


#endif
