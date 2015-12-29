#include "parselog.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

// The underscore indicates between the two respective categories
const int NUM_DIFF = 5;
const int NUM_INV = 16;
const int NUM_EYE = 21;
const int NUM_ORB = 26;
const int NUM_EPIC = 31;
const int DIFF_INV = NUM_INV - NUM_DIFF;
const int INV_EYE = NUM_EYE - NUM_INV;
const int EYE_ORB = NUM_ORB - NUM_EYE;
const int ORB_EPIC = NUM_EPIC - NUM_ORB;


void parse(ArrayList<HellRun*>& runs, string filename) {
	// Doing stuff to record info into HellRun object
	ifstream input(filename.c_str());
	string line;

	while (getline(input, line)) {
		if (line != "") {
			// bools to help know determine what program is looking at
			bool recordRun = true;
			bool recordDifficulty = false;
			bool recordInv = false;
			bool recordEye = false;
			bool recordOrb = false;
			bool recordEpic = false;

			// Variables to store each piece of data that makes up a HellRun
			string difficulty = "";
			string name = "";
			ArrayList<string> names;
			string sInt = "";
			int runNumber = 0;
			int invites = 0;
			int eyes = 0;
			int orbs = 0;
			unsigned int spacing = 0;

			for (unsigned int i = 0; i < line.length(); i++) {
				// Record the current run's number
				if (line[i] == ' ' && recordRun) {
					recordRun = false;
					runNumber = atoi(sInt.c_str());
					sInt = "";
				} else if (recordRun) {
					sInt += line[i];
				}

				// Recording the difficulty (by this time we will have found spacing too)
				if (line[i] != ' ' && !recordDifficulty && !recordRun) {
					spacing = i - NUM_DIFF;
					recordDifficulty = true;
					difficulty += line[i];
				// Keep going basically until we reach when it is time to record eyes
				} else if (recordDifficulty && i < NUM_INV + spacing && line[i] != ' ') {
					difficulty += line[i];
				// Time to record demon invitations
				} else if (i == NUM_INV + spacing) {
					recordInv = true;
					sInt += line[i];
				// Likewise, this case shouldn't ever happen but whatever
				} else if (recordInv && i < NUM_EYE + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record eye
				} else if (i == NUM_EYE + spacing) {
					recordEye = true;
					invites = atoi(sInt.c_str());
					sInt = line[i];
				// This case should probably never happen because impossible to get more than 5 eyes
				} else if (recordEye && i < NUM_ORB + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record orb
				} else if (i == NUM_ORB + spacing) {
					// If alphabetical character, means it's old version
					if (isalpha(line[i])) {
						input.close();
						parse_old(runs, filename);
						return;
					}
					recordOrb = true;
					eyes = atoi(sInt.c_str());
					sInt = line[i];
				// Ditto with the earlier case for eyes here
				} else if (recordOrb && i < NUM_EPIC + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record epics
				} else if (i == NUM_EPIC + spacing) {
					orbs = atoi(sInt.c_str());
					recordEpic = true;
					name += line[i];
				// If space found or we are at last character in the line, push name into names
				} else if (recordEpic && (line[i] == '/' || i == line.length()-1)) {
					if (line[i] != '/') name += line[i];
					if (lowercase(name) != "none") names.insert(names.size(), name);
					name = "";
				// If recordEpic is true and the character is not a space, add it to name
				} else if (recordEpic) {
					if (line[i] != '/') name += line[i];
				}

			} // end of for loop going through line

			HellRun* run = new HellRun(runNumber);

			if (lowercase(difficulty) == "insane")
				run->setDifficulty(true);
			if (names.size() != 0)
				run->setDropped(true);

			run->setEyes(eyes);
			run->setOrbs(orbs);
			run->addEpics(names);
			run->setInvites(invites);

			runs.insert(runs.size(), run);
		} // end of if (line != "")

	} // end of while loop
	input.close();
} // end of function


void parse_old(ArrayList<HellRun*>& runs, string filename) {
	// Doing stuff to record info into HellRun object
	ifstream input(filename.c_str());
	string line;

	while (getline(input, line)) {
		if (line != "") {
			// bools to help know determine what program is looking at
			bool recordRun = true;
			bool recordDifficulty = false;
			bool recordEye = false;
			bool recordOrb = false;
			bool recordEpic = false;

			// Variables to store each piece of data that makes up a HellRun
			string difficulty = "";
			string name = "";
			ArrayList<string> names;
			string sInt = "";
			int runNumber = 0;
			int eyes = 0;
			int orbs = 0;
			unsigned int spacing = 0;

			for (unsigned int i = 0; i < line.length(); i++) {
				// Record the current run's number
				if (line[i] == ' ' && recordRun) {
					recordRun = false;
					runNumber = atoi(sInt.c_str());
					sInt = "";
				} else if (recordRun) {
					sInt += line[i];
				}

				// Recording the difficulty (by this time we will have found spacing too)
				if (line[i] != ' ' && !recordDifficulty && !recordRun) {
					spacing = i - NUM_DIFF;
					recordDifficulty = true;
					difficulty += line[i];
				// Keep going basically until we reach when it is time to record eyes
				} else if (recordDifficulty && i < NUM_INV + spacing && line[i] != ' ') {
					difficulty += line[i];
				// Time to record eye
				} else if (i == NUM_INV + spacing) {
					recordEye = true;
					sInt += line[i];
				// This case should probably never happen because impossible to get more than 5 eyes
				} else if (recordEye && i < NUM_EYE + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record orb
				} else if (i == NUM_EYE + spacing) {
					recordOrb = true;
					eyes = atoi(sInt.c_str());
					sInt = line[i];
				// Ditto with the earlier case for eyes here
				} else if (recordOrb && i < NUM_ORB + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record epics
				} else if (i == NUM_ORB + spacing) {
					orbs = atoi(sInt.c_str());
					recordEpic = true;
					name += line[i];
				// If space found or we are at last character in the line, push name into names
				} else if (recordEpic && (line[i] == '/' || i == line.length()-1)) {
					if (line[i] != '/') name += line[i];
					if (lowercase(name) != "none") names.insert(names.size(), name);
					name = "";
				// If recordEpic is true and the character is not a space, add it to name
				} else if (recordEpic) {
					if (line[i] != '/') name += line[i];
				}

			} // end of for loop going through line

			HellRun* run = new HellRun(runNumber);

			if (lowercase(difficulty) == "insane")
				run->setDifficulty(true);
			if (names.size() != 0)
				run->setDropped(true);

			run->setEyes(eyes);
			run->setOrbs(orbs);
			run->addEpics(names);

			runs.insert(runs.size(), run);
		} // end of if (line != "")

	} // end of while loop
	input.close();
} // end of function


void output(ArrayList<HellRun*>& runs, string filename) {
	ofstream output(filename.c_str());
	string runNumber = intToString(runs[runs.size()-1]->getRunNum());
	int spacing = runNumber.length() - 1;

	for (int i = 0; i < runs.size(); i++) {
		// Outputting run number
		runNumber = intToString(runs[i]->getRunNum());
		output << runNumber;
		int numSpaces = NUM_DIFF + spacing - runNumber.length();

		// Adding appropriate spaces from number to difficulty
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}
		// Outputting difficulty
		string difficulty;
		if (runs[i]->getDifficulty())
			difficulty = "Insane";
		else
			difficulty = "Hardcore";

		output << difficulty;
		numSpaces = DIFF_INV - difficulty.length();


		// Adding appropriate spaces from difficulty to invites
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		// Outputting invites
		string invites = intToString(runs[i]->getInvites());

		output << invites;
		numSpaces = INV_EYE - invites.length();

		// Adding appropriate spaces from invites to eyes
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		// Outputting eyes
		string eyes = intToString(runs[i]->getEyes());

		output << eyes;
		numSpaces = EYE_ORB - eyes.length();

		// Adding appropriate spaces from eyes to orbs
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		// Outputting orbs
		string orbs = intToString(runs[i]->getOrbs());

		output << orbs;
		numSpaces = ORB_EPIC - orbs.length();

		// Adding appropriate spaces from orbs to epics
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		ArrayList<string> epics = runs[i]->getEpics();

		// Adding epics
		if (epics.size() == 0) {
			output << "None";
		} else {
			for (int j = 0; j < epics.size(); j++) {
				output << epics[j];
				if (epics.size() > 1 && j != epics.size()-1)
					output << '/';
			}
		}
		output << "\n";

	} // end of for loop
	output.close();
}


string nameCleanup(string s) {
	return s;
}

bool isNumber(string s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

string intToString(int n) {
	ostringstream ss;
	ss << n;
	return ss.str();
}


string ordIndicator(string s) {
	int number;
	istringstream ss(s);
	ss >> number;

	// For the "teens"
	if (19 % number < 10 && number < 20 && number > 9) {
		return "th";
	// 0 case
	} else if (number == 0 || number % 10 == 0) {
		return "th";
	// 1 case
	} else if (number == 1 || number % 10 == 1) {
		return "st";
	// 2 case
	} else if (number == 2 || number % 10 == 2) {
		return "nd";
	// 3 case
	} else if (number == 3 || number % 10 == 3) {
		return "rd";
	// 4-9 case
	} else {
		return "th";
	}
}


string lowercase(string s) {
	string result = "";
	for (unsigned int i = 0; i < s.length(); i++) {
		result += tolower(s[i]);
	}
	return result;
}

bool isValid(string input) {
	string filterInput = "";

	if (input.length() > 0) {
		filterInput += input[0];
		// Tries to find if somebody typed "none" with tons of spaces in between
		for (unsigned int i = 1; i < input.length() - 1; i++) {
			if (input[i] != ' ')
				filterInput += input[i];
		}
		filterInput += input[input.length()-1];
	}

	// If input is nothing or a user type "none" in any form (exluding numbers), return false
	if (input == "" || lowercase(input) == "none" || lowercase(filterInput) == "none")
		return false;
	else
		return true;
}