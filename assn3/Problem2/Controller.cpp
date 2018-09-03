#include "Controller.h"
Controller::Controller(){
  board = new Board;
  userA = new User(true, board);
  userB = new User(false, board);
  team = true;
  cnt = 2;
  A_king_stay = 0;
  B_king_stay = 0;
}

Controller::~Controller(){
	delete board;
  delete userA;
  delete userB;
}

int Controller::turn(){
  User* current = nullptr;
  if(team == true){
    cout << "Red Team Turn" << endl;
    current = userA;
  }
  else{
    cout << "Green Team Turn" << endl;
    current = userB;
  }

  int first_op=-1;
  int second_op = -1;
  int on_n = 0;
  int hl_n = 0;

  //chose which pieces
  while(1){
    int on_null_count = 0;
    int hl_null_count = 0;
    cout << "1. Move the lived pieces" << endl << "2. Use the hold pieces" << endl << ">> ";
    cin >> first_op;

    switch (first_op) {
		//if prompt user willing to move the lived pieces
		//read user's Onboardpieces info
		//check the number of pieces and save it into on_n variable
      case 1:{
        for(int i =0; i<7; i++){
          if(current->get_onpiece()[i] != nullptr){
            cout << i << ": [";
            current->get_onpiece()[i]->printPieces();
            cout << "]" << endl;
			on_n++;
          }
          else{
              on_null_count++;
          }
        }
        if(on_null_count == 7){
          cout << "There is no Pieces" << endl << endl;
          break;
        }
        else
          break;
      }
		//if prompt user willing to move the hed pieces
		//read user's HeldPieces info
		//check the number of pieces and save it into hl_n variable
      case 2:{
        for(int j =0; j<7; j++){
          if(current->get_heldpiece()[j] != nullptr){
            cout << j << ": [";
            current->get_heldpiece()[j]->printPieces();
            cout << "]" << endl;
			hl_n++;
          }
          else{
            hl_null_count++;
          }
        }
        if(hl_null_count == 7){
          cout << "There is no Pieces" << endl << endl;
          break;
        }
        else
          break;
      }
      default:
        cout << "Selected wrong. Please Select Again!" << endl << endl;
        break;
    }

	//if there is no problems with selecting pieces, then break while loop
	//if user input wrong operation number or there is no piece in the arrary
	//go back to the first
    if(first_op == 1 && on_null_count != 7)
      break;
    else if(first_op == 2 && hl_null_count != 7)
      break;
    continue;
  }

  //chosse the specific piece
  while(1){
    int x = -100;
    int y = -100;
    cout << ">> ";
    cin >> second_op;

	//using try-catch block
	//if user move piece into impossible location, then throw error
    try{
      if(first_op == 1 && 0 <= second_op && second_op < on_n){
        Piece* _piece = current->get_onpiece()[second_op];
        try{
          _piece->printPossibleLocation(board);
        }catch(int pos){
          cout << "There is no way to move. Select a different piece." << endl;
          continue;
        }

        cout << ">> "; cin >> x >> y;
        if(_piece->isPossibleMove(board, x, y))
          current->movePieces(_piece, board, x, y);
        else{
          cout << "Impossible location" << endl;
          throw 'e';
        }
        break;
      }

      else if(first_op == 2 && 0 <= second_op && second_op < hl_n){
        cout << ">> "; cin >> x >> y;
        if(board->get_piece(x, y) == nullptr){
          current->HeldtoOnboard(second_op, board, x, y);
          break;
        }
        else{
          std::cout << "Impossible location" << std::endl;
          throw 'e';
        }
      }

      else{
		  cout << "Selected wrong. Please select again!" << endl;
        continue;
      }
    }

    catch(char E){
      if(E == 'e')
        return 1;
    }
  }
  
  //before getting out of while loop, team will be changed and
  //cnt will be increased by 1
  team = !team;
  cnt++;
  return 1;
}

//update first and print last
//cnt will be represented by cnt/2
void Controller::printStatus(){
    cout << endl << static_cast<int>(cnt/2) << "th Turn" << endl;

    userA->update_Piece(board);
    userA->printUser();
    cout << endl;

    userB->update_Piece(board);
    userB->printUser();
    cout << endl;

    board->printBoard();
}

//King is held
//King is stayed for a turn
bool Controller::isEnded(){
  Piece** A_hl_p = userA->get_heldpiece();
  Piece** A_on_p = userA->get_onpiece();
  Piece** B_hl_p = userB->get_heldpiece();
  Piece** B_on_p = userB->get_onpiece();


  if(team == true){
    for(int i =0; i<7; i++){
		//if king is held with checking "isking" info in every Heldpieces array
		//game will be ended
      if(B_hl_p[i] != nullptr && B_hl_p[i]->get_king() == 1){
        cout << "Green Team Win!" << endl;
        return true;
      }

		//or if king is stayed in the territory of oppostie team.
		//comparsion between how long the king stays and the cnt count
      if(B_on_p[i] != nullptr && B_on_p[i]->get_king() == 1){
        int king_x = B_on_p[i]->get_x();
        //(0,0), (0,1), (0,2)
        if(king_x == 0)
          B_king_stay++;
        else
          B_king_stay = 0;

		if (A_king_stay == 1) {
			cout << "Red Team win!" << endl;
			return true;
		}
      }
    }
  }
  else{

    for(int i =0; i<7; i++){
      if(A_hl_p[i] != nullptr && A_hl_p[i]->get_king() == 1){
        cout << "Red Team Win!" << endl;
        return true;
      }

      if(A_on_p[i] != nullptr && A_on_p[i]->get_king() == 1){
        int king_x = A_on_p[i]->get_x();
        //(3,0), (3,1), (3,2)
        if(king_x == 3)
          A_king_stay++;
        else
          A_king_stay = 0;

        if(B_king_stay == 1) {
			cout << "Green Team Win!" << endl;
			return true;
		}
      }
    }
  }

  return false;
}
