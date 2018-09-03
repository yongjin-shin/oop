#ifndef _FIREPOK_H_
#define _FIREPOK_H_

#include "Poketmon.h"

class FirePok:public Poketmon{
public:
  FirePok(std::string type, double atk, double df, double hp):Poketmon(type, atk, df, hp){}
  ~FirePok(){};
  virtual int battle(Poketmon* B);
};

#endif
