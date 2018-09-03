#include "Scene.h"
#include <fstream>
#include <string>

int main() {

	ifstream infile;
	infile.open("input.txt");
	if(!infile.is_open()){
		cout << "Cannot open Input.txt";
		return 200;
	}

	int count;
	string op;
	int n;
	double x,y;

	infile >> count;
	Scene<Polygon<double> >* place = new Scene<Polygon<double> >[count];
	int i = -1;
	while (!infile.eof()) {
		infile >> op;
		if (op == "s") {
			i++;
			place[i] = Scene<Polygon<double> >();
			infile >> n;
		}
		else
			n = stoi(op);

		vector<Point<double> > tmp;
		for (int i = 0; i<n; i++) {
			infile >> x >> y;
			Point<double> p(x, y);
			tmp.push_back(p);
		}
		Polygon<double> poly(n, tmp);
		place[i].ary.push_back(poly);
	}



	for (int i = 0; i < count; i++) {
		cout << "S" << i << endl;
		vector<Point<int> > storage;//for storing the index of two polygon
		for (int j = 0; j < place[i].ary.size(); j++) {
			for (int k = 0; k < place[i].ary.size(); k++) {
				Polygon<double> _pl = place[i].ary[j] - place[i].ary[k];
				Polygon<double> _ch = _pl.convexHull();
				if (_ch.IsCollide() && j != k) {
					Point<int> el(j, k);//A-B
					Point<int> re_el(k, j);//convex Hull of A-B
					int success = 1;
					//if there is same element in the storage
					//i.e. (x,y) = (y,x)
					for (int i = 0; i < storage.size(); i++) {
						if (storage[i] == re_el) {
							success--;
							break;
						}
					}
					if (success)
						storage.push_back(el);
				}
			}
		}
		for (int i = 0; i < storage.size(); i++)
			cout << storage[i].x << "-" << storage[i].y << endl;
	}

	/*
	Point<double> p0(0, 0);
	Point<double> p1(1, 0);
	Point<double> p2(0, 1);
	Point<double> q0(1, 1);
	Point<double> q1(-1, -1);
	Point<double> q2(0, -1);
	//Point<double> q3(1, 2);

	Polygon<double> P, Q, R;
	P.add(p0); P.add(p1); P.add(p2);
	Q.add(q0); Q.add(q1); Q.add(q2); //Q.add(q3);
	cout << P.distance(Q);
	*/

	delete[] place;
	return 0;
}
