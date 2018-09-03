#include "CircleCollider.h"
#include "BoxCollider.h"
#include <fstream>
using namespace std;

int main() {
	string choose1;
	string choose2;
	Vector2D p1 = { 0,0 };
	Vector2D p2 = { 0,0 };
	Vector2D p3 = { 0,0 };
	CircleCollider c1(p1, p2, p3);
	CircleCollider c2(p1, p2, p3);
	BoxCollider b1(p1, p2, p3);
	BoxCollider b2(p1, p2, p3);

	ifstream myfile("input.txt");
	if (!myfile.is_open()){
		cout << "Unable to open file";
	}


	while (!myfile.eof()) {
		myfile >> choose1;//get first collider's postions
		myfile >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
		if (choose1.compare("C") == 0) {
			CircleCollider tmp1(p1, p2, p3);
			c1 = tmp1;
		}
		else {
			BoxCollider tmp1(p1, p2, p3);
			b1 = tmp1;
		}


		myfile >> choose2;//get second collider's postions
		myfile >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
		if (choose2.compare("C") == 0) {
			CircleCollider tmp2(p1, p2, p3);
			c2 = tmp2;
		}
		else {
			BoxCollider tmp2(p1, p2, p3);
			b2 = tmp2;
		}

		//check whether two collider are instecting, containing or separated
		if (choose1.compare("C") == 0) {
			c1.printResult(c2);
		}
		else if (choose1.compare("B") == 0 && choose1.compare("C") == 0) {

		}


	}


	return 0;

}