#include "Board.h"

Board::Board(){
  piece[0][0] = new Bishop(0, 0, true, 0);
  piece[0][1] = nullptr;
  piece[0][2] = nullptr;
  piece[0][3] = new Rook(3, 0, false, 0);
  piece[1][0] = new King(0, 1, true, 1);
  piece[1][1] = new Pawn(1, 1, true, 0);
  piece[1][2] = new Pawn(2, 1, false, 0);
  piece[1][3] = new King(3, 1, false, 1);
  piece[2][0] = new Rook(0, 2, true, 0);
  piece[2][1] = nullptr;
  piece[2][2] = nullptr;
  piece[2][3] = new Bishop(3, 2, false, 0);
}

Board::~Board(){

}

void Board::changePiece(Piece* new_p, int _x, int _y){
  piece[_y][_x] = new_p;
}

void Board::printBoard(){
  std::cout << "---------------------" << std::endl;
  for(int i = 0; i<3; i++){
    for(int j=0; j<4; j++){
      std::cout << "| ";
      if(piece[i][j] != nullptr)
        piece[i][j]->printPieces();
      else
        std::cout << "  ";
      std::cout << " ";
    }
    std::cout << "| ";
    std::cout << std::endl;
    if(i==2)
      break;
    std::cout << "---------------------" << std::endl;
  }
  std::cout << "---------------------" << std::endl;
}
