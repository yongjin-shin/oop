#include "Controller.h"

int main(void) {
	Controller *control = new Controller();
	do {
		control->printStatus();
		control->turn();
	} while (!control->isEnded());
	delete control;
}