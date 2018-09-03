#ifndef _PAIRS_H_
#define _PAIRS_H_

#include <string>

template <class T1, class T2>
class Pair {
private:
    T1 e1;
    T2 e2;

public:
  Pair(T1 e1, T2 e2);


};

template <class T1, class T2>
Pair<T1, T2>::Pair(T1 e1, T2 e2){
  this->e1 = e1;
  this->e2 = e2;
}

#endif
