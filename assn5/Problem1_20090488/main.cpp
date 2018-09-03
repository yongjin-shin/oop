#include "Set.cpp"

int main(){
  string element1[5] = {"a", "b", "c", "d", "e"};
  string element2[3] = {"f", "g", "h"};

  Set<string> A(5, element1);
  Set<string> B(3, element2);
  Set<string> C;
  Set<Set<string> > D;

   C = A-B;
   C.print();

  //  A.print();
  //  B.print();

   D = C.powerSet();
  //  cout << D.get_elements();


  //  bool result = !(A==B);
  //  cout << result << endl;


  return 0;
}
