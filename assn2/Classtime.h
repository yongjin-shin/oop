#include <iostream>

namespace Name{
	enum Day{Non=0, Mon, Thu, Wed, Thur, Fri, Sat, Sun=7};
}

class ClassTime {
public:
	ClassTime(Name::Day classtime_day, int classtime_start, int classtime_end);
	~ClassTime();
	Name::Day getclasstime_day();
	int getclasstime_start();
	int getclasstime_end();

private:
	Name::Day classtime_day;
	int classtime_start;
	int classtime_end;
};
