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
	/*
	cout << "Does this work?" << endl;
	currRun = new HellRun(1);
	list.insert(list.size(), currRun);
	cout << "Run number: " << list[0]->getRunNum() << endl;
	*/
	ArrayList<string> aList;
	aList.insert(aList.size(), "bro");
	aList.insert(aList.size(), "Ranger rod plz");
	aList.insert(aList.size(), "Silver bullet when");
	ArrayList<string> myList = aList;

	for (int i = 0; i < myList.size(); i++) {
		cout << myList[i] << endl;
	}

}

int main() {
	TestClass test;
	cout << "Hey bro" << endl;

	return 0;
}