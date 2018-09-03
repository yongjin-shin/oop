#include "Bishop.h"
#include "Board.h"

//Bishop.can move FOR_RIGHT, BACK_RIGH, FOR_LEFT, BACK_LEFT
//compare between where Bishop can be moved and where the user willing to move
//if they are same, then return ture, otherwise return false
bool Bishop::isPossibleMove(Board* board, int _x, int _y){
  int here_x = this->get_x();
  int here_y = this->get_y();
  if(0<=_x && _x<=3 && 0<=_y && _y<=2){
    for(int i =FOR_RIGHT; i<=FOR_LEFT; i++){
      int there_x = here_x+(this->get_pattern()+i)->_x;
      int there_y = here_y+(this->get_pattern()+i)->_y;
      if(there_x == _x && there_y == _y && board->get_piece(_x, _y) == nullptr)
        return true;
      else if(there_x == _x && there_y == _y && board->get_piece(_x, _y)->get_team() != this->get_team())
        return true;
    }
  }
  return false;
}

//Bishop.can move FOR_RIGHT, BACK_RIGH, FOR_LEFT, BACK_LEFT
//With using struct Patter, easily calculate pos_x and pos_y of piece
void Bishop::printPossibleLocation(Board* board){
  int pos = 0;
  std::cout << "Bishop: possible location to move" << std::endl;
  for(int i =FOR_RIGHT; i<=FOR_LEFT; i++){
    int move_x = this->get_x()+(this->get_pattern()+i)->_x;
    int move_y = this->get_y()+(this->get_pattern()+i)->_y;
    if(this->isPossibleMove(board, move_x, move_y)){
      std::cout << "(" << move_x << ", " << move_y << ")" << std::endl;
      pos++;
    }
  }
    if(pos == 0)
      throw 1;
}

void Bishop::printPieces(){
  char t_name;
  if(this->get_team() == true)
    t_name = 'R';
  else
    t_name = 'G';
  std::cout << 'B' << t_name;
}
