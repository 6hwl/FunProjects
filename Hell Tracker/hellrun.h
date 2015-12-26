#ifndef HELLRUN_H
#define HELLRUN_H

#include <string>
#include <vector>

class HellRun {
public:
	HellRun(int curr); // defaults to HARDCORE!!!
	~HellRun();

	void setDifficulty(bool b); // Set if Insane or Hardcore; true is insane
	void addEpic(std::string name); // Set an epic to the vector
	void addEpics(std::vector<std::string> other_epics); // Set epics = other_epics
	void setDropped(bool b); // Set if an epic dropped
	void setRunNum(int n); // Set the number of the run
	void setEyes(int n); // Set the number of eyes dropped
	void setOrbs(int n); // Set the number of orbs dropped

	bool getDifficulty(); // Returns false if hardcore, true if insane
	std::vector<std::string> getEpics(); // Return the vector containing epics dropped
	int getRunNum(); // Returns which run this is (e.g. the 7th run)
	bool getDropped(); // Returns true if epic_dropped is true, false otherwise
	int getEyes(); // Return number of eyes
	int getOrbs(); // Return number of orbs

private:
	int run_number;
	int eyes;
	int orbs;
	bool insane;
	bool epic_dropped;
	std::vector<std::string> epics;
	

};

#endif