#include "Link.h"
#include <fstream>
#include <string>
using namespace std;

int main(void){

  double theta0 = 0.0;//default
  int cnt = 1;
  string sl1, sl2, sl3, stheta1, stheta2;
  double l1, l2, l3, theta1, theta2;
  ifstream infile("input.txt");
  if (!infile.is_open()) {
	  cout << "Unable to open file";
	  return 200;
  }

	while (!infile.eof()) {
		infile >> sl1 >> sl2 >> sl3 >> stheta1 >> stheta2;
		l1 = stod(sl1);
		l2 = stod(sl2);
		l3 = stod(sl2);

		theta1 = stod(stheta1);
		theta2 = stod(stheta2);

		Link* li0 = new Link(l1, -theta0, nullptr);
		Link* li1 = new Link(l2, -theta0 - theta1, li0);
		Link* li2 = new Link(l3, -theta0 - theta1 - theta2, li1);

		cout << cnt << ". " <<li2->getEndPoint().toString() << endl;
		cnt++;
	}

  return 0;
}
