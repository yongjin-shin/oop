#include "User.h"

//Read all the possible location in board and
//if the location has value which has the same team info
//then, put the address of that location in either onboardpiece or heldpiece array
User::User(bool team, Board* board){
  this->team = team;
  int on=0;

  for(int i =0; i<4;i++){
    for(int j=0; j<3; j++){
      if(board->get_piece(i,j) != nullptr && board->get_piece(i,j)->get_team() == this->team){
        OnboardPiece[on] = board->get_piece(i,j);
        on++;
      }
    }
  }

  for(int i =0; i<7; i++)
    HeldPiece[i] = nullptr;
}

//destruct every piece in the Onboardpiece array
User::~User(){
	for (int i = 0; i < 7; i++) {
		if (OnboardPiece[i] != nullptr)
			delete OnboardPiece[i];
	}
}

//Read the board info an change both the Onboard and the HeldPiece array
//the piece address will be stocked one after another with no vacancy
void User::update_Piece(Board* board){
  for(int i =0; i<7; i++)
    OnboardPiece[i] = nullptr;

  int on=0;

  for(int i =0; i<4;i++){
    for(int j=0; j<3; j++){
      if(board->get_piece(i,j) != nullptr && board->get_piece(i,j)->get_team() == this->team && board->get_piece(i,j)->get_isHeld() != 1){
        OnboardPiece[on] = board->get_piece(i,j);
        on++;
      }
    }
  }

  int _held = 0;
  Piece* tmp[7];
  for(int i =0; i<7; i++){
    tmp[i] = HeldPiece[i];
  }

  for(int i =0; i<7; i++){
    if(tmp[i] != nullptr){
      HeldPiece[_held] = tmp[i];
      _held++;
    }
  }
}

//print User info one by one
void User::printUser(){
  if(team == true)
    std::cout << "Red Team";
  else
    std::cout << "Green Team";

  std::cout << std::endl << "Lived Pieces: ";
  for(int i=0; i<7; i++){
    if(OnboardPiece[i] != nullptr){
      std::cout << " [";
      OnboardPiece[i]->printPieces();
      std::cout<< "] ";
    }
  }

  std::cout << std::endl << "Held Pieces: ";
  for(int i=0; i<7; i++){
    if(HeldPiece[i] != nullptr){
      std::cout << " [";
      HeldPiece[i]->printPieces();
      std::cout<< "] ";
    }
  }
  std::cout << std::endl;
}

//the action of movement by user
//if the location of where the user want to move piece into
//is not nullptr, just call "Setpiece" method
//otherwise, if there is opposite team's piece, then get it into the held array
void User::movePieces(Piece* on_piece, Board* board, int _x, int _y){
  if(board->get_piece(_x, _y) != nullptr && board->get_piece(_x, _y)->get_team() != team){
    for(int i =0; i<7; i++){
      if(HeldPiece[i] == nullptr){
        HeldPiece[i] = board->get_piece(_x, _y);
        HeldPiece[i]->heldChange();
        board->changePiece(nullptr, _x, _y);
        break;
      }
    }
  }
  else if(board->get_piece(_x, _y) != nullptr && board->get_piece(_x, _y)->get_team() == team){
    std::cout << "Wrong Move!" << std::endl;
    return;
  }
  on_piece->setPieces(board, _x, _y);
}

//instead of moving, if the user are willing to use one of heldpieces,
//before being on board, piece's info will be changes such as team, positions and held status
void User::HeldtoOnboard(int held, Board* board, int _x, int _y){
    HeldPiece[held]->teamChange();
    HeldPiece[held]->setPieces(board, _x, _y);
    HeldPiece[held]->heldChange();
    HeldPiece[held]=nullptr;
}
