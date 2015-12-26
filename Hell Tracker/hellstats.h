#ifndef HELLSTATS_H
#define HELLSTATS_H

#include "hellrun.h"
#include <vector>

class HellStats {
public:
	HellStats(std::vector<HellRun*>& runs);
	void update(std::vector<HellRun*>& runs);
	int getHardcores();
	int getEyes();
	int getOrbs();
	int getEpics();


private:
	int stats[4];
	// index 0 = number of hardcores
	// index 1 = number of demon eyes
	// index 2 = number of hell orbs
	// index 3 = number of epics
};


#endif