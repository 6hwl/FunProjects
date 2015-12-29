#ifndef BINSEARCH_H
#define BINSEARCH_H

#include <vector>
#include "hellrun.h"

int binarySearch(ArrayList<HellRun*>& runs, int lower, int upper, int value);

// This function will only work if value is less than the run number of the last element.
// It is a specific implementation of binarySearch which finds where to insert a HellRun*
int getInsertionIndex(ArrayList<HellRun*>& runs, int lower, int upper, int value);

#endif