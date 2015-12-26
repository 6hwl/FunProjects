#include "hellstats.h"
#include <iostream>

using namespace std;

HellStats::HellStats(vector<HellRun*>& runs) {
	update(runs);
}

void HellStats::update(vector<HellRun*>& runs) {
	// Initialize the private member array
	for (int i = 0; i < 4; i++) {
		stats[i] = 0;
	}

	for (unsigned int i = 0; i < runs.size(); i++) {
		if (runs[i]->getDifficulty() == false) stats[0] += 1;
		stats[1] += runs[i]->getEyes();
		stats[2] += runs[i]->getOrbs();
		stats[3] += runs[i]->getEpics().size();
	}

}

int HellStats::getHardcores() {
	return stats[0];
}

int HellStats::getEyes() {
	return stats[1];
}

int HellStats::getOrbs() {
	return stats[2];
}

int HellStats::getEpics() {
	return stats[3];
}

