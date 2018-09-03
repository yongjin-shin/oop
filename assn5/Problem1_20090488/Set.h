#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include <fstream>


using namespace std;

template <class T>
class Set {
private:
  T* elements;
  int size;
public:
  Set();
  Set(int size, T* elements);
  ~Set();
  Set operator+(const Set& set);
  Set operator+(const T element);
  Set operator-(const Set& set);
  Set operator-(const T element);
  Set operator*(const Set& set);
  Set& operator=(const Set& set);
  bool operator==(const Set& set);
  bool contains(const T element);
  friend std::ostream& operator<<(std::ostream&, const Set&);
  Set<Set<T> > powerSet();
  bool isSubsetOf(const Set& set);
  Set intersection(const Set& set);
  void print();
  T* get_elements(){return this->elements;}
};

#endif
