#include "Pawn.h"
#include "Board.h"

//Pawn.can move Only one side, FORWARD
//However, the opposite team's pawn can be moved BACKWARD
//compare between where Pawn can be moved and where the user willing to move
//if they are same, then return ture, otherwise return false
bool Pawn::isPossibleMove(Board* board, int _x, int _y){
  int here_x = this->get_x();
  int here_y = this->get_y();
  if(0<=_x && _x<=3 && 0<=_y && _y<=2){
    if(this->get_team() == true){
      for(int i =FOR; i<RIGHT; i++){
        int there_x = here_x+(this->get_pattern()+i)->_x;
        int there_y = here_y+(this->get_pattern()+i)->_y;
        if(there_x == _x && there_y == _y && board->get_piece(_x, _y) == nullptr)
          return true;
        else if(there_x == _x && there_y == _y && board->get_piece(_x, _y)->get_team() != this->get_team())
          return true;
      }
    }
    else{
      for(int i =BACK; i<LEFT; i++){
        int there_x = here_x+(this->get_pattern()+i)->_x;
        int there_y = here_y+(this->get_pattern()+i)->_y;
        if(there_x == _x && there_y == _y && board->get_piece(_x, _y) == nullptr)
          return true;
        else if(there_x == _x && there_y == _y && board->get_piece(_x, _y)->get_team() != this->get_team())
          return true;
      }
    }
  }
  return false;
}

//Rook.can move FORWARD
//With using struct Patter, easily calculate pos_x and pos_y of piece
void Pawn::printPossibleLocation(Board* board){
  int pos = 0;
  std::cout << "Pawn: possible location to move" << std::endl;

  if(this->get_team() == true){
    for(int i =FOR; i<RIGHT; i++){
      int move_x = this->get_x()+(this->get_pattern()+i)->_x;
      int move_y = this->get_y()+(this->get_pattern()+i)->_y;
      if(this->isPossibleMove(board, move_x, move_y)){
        std::cout << "(" << move_x << ", " << move_y << ")" << std::endl;
        pos++;
      }
    }
  }
  else{
    for(int i =BACK; i<LEFT; i++){
      int move_x = this->get_x()+(this->get_pattern()+i)->_x;
      int move_y = this->get_y()+(this->get_pattern()+i)->_y;
      if(this->isPossibleMove(board, move_x, move_y)){
        std::cout << "(" << move_x << ", " << move_y << ")" << std::endl;
        pos++;
      }
    }
  }

  if(pos == 0)
    throw 1;
}

void Pawn::printPieces(){
  char t_name;
  if(this->get_team() == true)
    t_name = 'R';
  else
    t_name = 'G';
  std::cout << 'P' << t_name;
}
