#include "WaterPok.h"

int WaterPok::battle(Poketmon* B){
  double a_atk = this->get_atk();
  double a_df = this->get_df();
  double a_hp = this->get_hp();
  double b_atk = B->get_atk();
  double b_df = B->get_df();
  double b_hp = B->get_hp();

  if(B->get_type().compare("Grass")==0){
    a_atk *= 1.5;
    b_df *= 0.8;
  }
  else if(B->get_type().compare("Fire")==0){
    a_df *= 0.8;
    b_atk *= 1.5;
  }

    while(1){
      if(b_atk <= a_df)
        a_hp -= 1;
      else
        a_hp -= b_atk - a_df;

      if(a_atk <= b_df)
        b_hp -=1;
      else
        b_hp -= a_atk - b_df;

      if(a_hp <= 0||b_hp<=0)
        break;
    }

    if(a_hp<=0 && b_hp<=0)
      return 0;
    else if(a_hp<=0)
      return 2;
    else
      return 1;
  }
