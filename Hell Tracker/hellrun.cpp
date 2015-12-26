#include "hellrun.h"

using namespace std;

// A Hell Mode object will default to hardcore mode
// and no epic dropping.

HellRun::HellRun(int curr) {
	run_number = curr;
	eyes = 0;
	orbs = 0;
	insane = false; // Defaults to hardcore mode
	epic_dropped = false;
}

HellRun::~HellRun() {}

void HellRun::setDifficulty(bool b) {
	insane = b;
}

void HellRun::addEpic(string name) {
	epics.push_back(name);
}

void HellRun::addEpics(std::vector<string> other_epics) {
	epics = other_epics;
}

void HellRun::setDropped(bool b) {
	epic_dropped = b;
}

void HellRun::setRunNum(int n) {
	run_number = n;
}

void HellRun::setEyes(int n) {
	eyes = n;
}

void HellRun::setOrbs(int n) {
	orbs = n;
}



bool HellRun::getDifficulty() {
	return insane;
}

vector<string> HellRun::getEpics() {
	return epics;
}

int HellRun::getRunNum() {
	return run_number;
}

bool HellRun::getDropped() {
	return epic_dropped;
}

int HellRun::getEyes() {
	return eyes;
}

int HellRun::getOrbs() {
	return orbs;
}