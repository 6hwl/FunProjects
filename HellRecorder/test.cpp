#include <iostream>
#include "hellrun.h"
#include "arraylist.h"

using namespace std;

class TestClass {
public:
	TestClass();

private:
	ArrayList<HellRun*> list;
	HellRun* currRun;

};

TestClass::TestClass() {
	cout << "Does this work?" << endl;
	currRun = new HellRun(1);
	list.insert(list.size(), currRun);
	cout << "Run number: " << list[0]->getRunNum() << endl;

}

int main() {
	TestClass test;
	cout << "Hey bro" << endl;

	return 0;
}