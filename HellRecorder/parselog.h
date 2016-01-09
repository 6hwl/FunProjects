#ifndef PARSELOG_H
#define PARSELOG

#include "hellrun.h"
#include <vector>
#include "arraylist.h"

/* This file was originally made for my parsing functions, 
** but I have just made it contain all of my etc. functions
** that are used to help me do certain things
*/


// Parses the information from log.txt into respective containers
void parse(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics, std::string filename);

// Old version of parse function to accomodate older versions of the program
void parse_old(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics, std::string filename);

// Outputs all of the information currently in runs to log.txt
void output(ArrayList<HellRun*>& runs, std::string filename);

// TODO
std::string nameCleanup(std::string s);

// Determines if a string is a number
bool isNumber(std::string s);

// Converts an int to a string using stringstream
std::string intToString(int n);

// Determines the ordinal indicator of a given number
std::string ordIndicator(std::string s);

// Converts a string to all lowercase characters
std::string lowercase(std::string s);

// Determines if an input for an epic name is invalid
bool isValid(std::string input);

// Gets the name of the file to read from (in config.txt)
std::string getFilename();

// Outputs into "config.txt" the defaults
std::string standardOutput();


#endif