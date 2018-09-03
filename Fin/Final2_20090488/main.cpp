#include "Harris.h"
#include <string>

int main() {

	ifstream infile;
	infile.open("input.txt");
	if (!(infile.is_open())) {
		cout << "Cannot open input.txt file" << endl;
		return 200;
	}

	int num;
	string file_name;
	while (!infile.eof()) {
		infile >> num;
		for (int i = 0; i < num; i++) {
			infile >> file_name;
			Harris hey(file_name);
			hey.print_corner();
		}
	}
	return 0;
}