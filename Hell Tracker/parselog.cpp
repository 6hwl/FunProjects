#include "parselog.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

// The underscore indicates between the two respective categories
const int NUM_DIFF = 5;
const int NUM_EYE = 16;
const int NUM_ORB = 21;
const int NUM_EPIC = 26;
const int DIFF_EYE = NUM_EYE - NUM_DIFF;
const int EYE_ORB = NUM_ORB - NUM_EYE;
const int ORB_EPIC = NUM_EPIC - NUM_ORB;
/*
void parse(vector<HellRun*>& runs) {
	// Doing stuff to record info into HellRun object
	ifstream input("log.txt");
	string line;

	while (getline(input, line)) {
		bool recordDifficulty = false;
		bool recordEpic = false;

		string difficulty = "";
		string name = "";
		string sNumber = "";
		int number = 0;

		if (line != "") {
			// @ NUM_DIFFICULTY index, difficulty starts
			// @ NUM_EPIC index, epic name starts
			for (unsigned int i = 0; i < line.length(); i++) {
				// If we have parsed the number and are at the difficulty
				if (i == NUM_DIFFICULTY && line[i] != ' ')
					recordDifficulty = true;
				else if (i == NUM_EPIC && line[i] != ' ')
					recordEpic = true;

				// For parsing which number hell run it is, then for difficulty, then epic name
				if (!recordDifficulty && line[i] != ' ') {
					sNumber += line[i];
				} else if (recordDifficulty && !recordEpic && line[i] != ' ') {
					difficulty += line[i];
				} else if (recordEpic) {
					name += line[i];
				}
			}

			number = atoi(sNumber.c_str());

			HellRun* run = new HellRun(number);

			if (difficulty == "Insane")
				run->setDifficulty(true);

			if (name != "") {
				run->setDropped(true);
				run->setEpic(name);
			}

			runs.push_back(run);

			
			//cout << "Run number: " << run->getRunNum() << endl;
			//cout << "Difficulty: " << run->getDifficulty() << endl;
			//cout << "Got an epic?: " << run->getEpic() << endl;
			
		}

	}

	input.close();
}
*/



void parse(vector<HellRun*>& runs, string filename) {
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
			vector<string> names;
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
				} else if (recordDifficulty && i < NUM_EYE + spacing && line[i] != ' ') {
					difficulty += line[i];
				// Time to record eye
				} else if (i == NUM_EYE + spacing) {
					recordEye = true;
					sInt += line[i];
				// This case should probably never happen because impossible to get more than 5 eyes
				} else if (recordEye && i < NUM_ORB + spacing && line[i] != ' ') {
					sInt += line[i];
				// Time to record orb
				} else if (i == NUM_ORB + spacing) {
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
					if (lowercase(name) != "none") names.push_back(name);
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

			runs.push_back(run);
		} // end of if (line != "")

	} // end of while loop

} // end of function


void output(std::vector<HellRun*>& runs, string filename) {
	ofstream output(filename.c_str());
	string runNumber = intToString(runs[runs.size()-1]->getRunNum());
	int spacing = runNumber.length() - 1;

	for (unsigned int i = 0; i < runs.size(); i++) {
		runNumber = intToString(runs[i]->getRunNum());
		output << runNumber;
		int numSpaces = NUM_DIFF + spacing - runNumber.length();

		// Adding appropriate spaces from number to difficulty
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		string difficulty;
		if (runs[i]->getDifficulty())
			difficulty = "Insane";
		else
			difficulty = "Hardcore";

		output << difficulty;
		numSpaces = DIFF_EYE - difficulty.length();

		// Adding appropriate spaces from difficulty to eyes
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		string eyes = intToString(runs[i]->getEyes());

		output << eyes;
		numSpaces = EYE_ORB - eyes.length();

		// Adding appropriate spaces from eyes to orbs
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		string orbs = intToString(runs[i]->getOrbs());

		output << orbs;
		numSpaces = ORB_EPIC - orbs.length();

		// Adding appropriate spaces from orbs to epics
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		vector<string> epics = runs[i]->getEpics();

		// Adding epics
		if (epics.size() == 0) {
			output << "None";
		} else {
			for (unsigned int j = 0; j < epics.size(); j++) {
				output << epics[j];
				if (epics.size() > 1 && j != epics.size()-1)
					output << '/';
			}
		}
		output << "\n";

	} // end of for loop

}


//TODO
/*
void output(std::vector<HellRun*>& runs) {
	ofstream output("log.txt");

	for (unsigned int i = 0; i < runs.size(); i++) {
		string runNumber = intToString(runs[i]->getRunNum());
		output << runNumber;
		int numSpaces = NUM_DIFFICULTY - runNumber.length();

		// Adding appropriate spaces for my formatting
		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		string difficulty;
		if (runs[i]->getDifficulty())
			difficulty = "Insane";
		else
			difficulty = "Hardcore";

		output << difficulty;
		numSpaces = DIFFICULTY_EPIC - difficulty.length();

		for (int j = 0; j < numSpaces; j++) {
			output << ' ';
		}

		output << runs[i]->getEpics().at(0) + "\n";

	}

}
*/

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