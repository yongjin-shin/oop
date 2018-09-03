#ifndef _POKETMON_H_
#define  _POKETMON_H_

#include <iostream>
#include <string>

class Poketmon{
private:
  std::string type;
  double atk;
  double df;
  double hp;

public:
  Poketmon(std::string type, double atk, double df, double hp){
    this->type = type; this->atk = atk; this->df = df; this->hp=hp; }
  virtual ~Poketmon(){};
  virtual int battle(Poketmon* B)=0;
  double get_atk(){return atk;}
  double get_df(){return df;}
  double get_hp(){return hp;}
  std::string get_type(){return type;}
};


#endif
