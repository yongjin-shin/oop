#ifndef _GRASSPOK_H_
#define _GRASSPOK_H_

#include "Poketmon.h"

class GrassPok:public Poketmon{
public:
  GrassPok(std::string type, double atk, double df, double hp):Poketmon(type, atk, df, hp){}
  ~GrassPok(){};
  virtual int battle(Poketmon* B);
};

#endif
