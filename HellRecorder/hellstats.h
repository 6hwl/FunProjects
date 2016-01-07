#ifndef HELLSTATS_H
#define HELLSTATS_H

#include "hellrun.h"
#include <vector>
#include "arraylist.h"

class HellStats {
public:
	HellStats(ArrayList<HellRun*>& runs);
	void update(ArrayList<HellRun*>& runs);
	int getHardcores();
	int getEyes();
	int getOrbs();
	int getEpics();
	int getInvites();
	int getHardcoreEpics();


private:
	int stats[6];
	// index 0 = number of hardcores
	// index 1 = number of demon invitations
	// index 2 = number of demon eyes
	// index 3 = number of hell orbs
	// index 4 = number of epics
	// index 5 = number of hardcore epics
};


#endif