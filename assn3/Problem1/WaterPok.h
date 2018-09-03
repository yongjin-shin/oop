#ifndef _WATERPOK_H_
#define _WATERPOK_H_

#include "Poketmon.h"

class WaterPok:public Poketmon{
public:
  WaterPok(std::string type, double atk, double df, double hp):Poketmon(type, atk, df, hp){}
  ~WaterPok(){};
  virtual int battle(Poketmon* B);
};

#endif
