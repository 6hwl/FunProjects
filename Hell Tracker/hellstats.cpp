#include "hellstats.h"
#include <iostream>

using namespace std;

HellStats::HellStats(ArrayList<HellRun*>& runs) {
	update(runs);
}

void HellStats::update(ArrayList<HellRun*>& runs) {
	// Initialize the private member array
	for (int i = 0; i < 5; i++) {
		stats[i] = 0;
	}

	for (int i = 0; i < runs.size(); i++) {
		if (runs[i]->getDifficulty() == false) stats[0] += 1;
		stats[1] += runs[i]->getInvites();
		stats[2] += runs[i]->getEyes();
		stats[3] += runs[i]->getOrbs();
		stats[4] += runs[i]->getEpics().size();
	}

}

int HellStats::getHardcores() {
	return stats[0];
}

int HellStats::getInvites() {
	return stats[1];
}

int HellStats::getEyes() {
	return stats[2];
}

int HellStats::getOrbs() {
	return stats[3];
}

int HellStats::getEpics() {
	return stats[4];
}

