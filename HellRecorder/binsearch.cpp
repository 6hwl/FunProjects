#include "binsearch.h"
#include <vector>
#include <iostream>

using namespace std;

int binarySearch(ArrayList<HellRun*>& runs, int lower, int upper, int value) {
	int index;
	int pivot = (lower + upper) / 2;

	if (lower > upper) {
		return -1;
	} else if (runs[pivot]->getRunNum() == value) {
		return pivot;
	} else if (value < runs[pivot]->getRunNum()) {
		index = binarySearch(runs, lower, pivot - 1, value);
	} else {
		index = binarySearch(runs, pivot + 1, upper, value);
	}

	return index;
}

int getInsertionIndex(ArrayList<HellRun*>& runs, int lower, int upper, int value) {
	int index;
	int pivot = (lower + upper) / 2;

	if (lower == upper) {
		if (value < runs[lower]->getRunNum()) return lower;
		else return lower + 1;
	} else if (value < runs[pivot]->getRunNum()) {
		index = getInsertionIndex(runs, lower, pivot - 1, value);
	} else {
		index = getInsertionIndex(runs, pivot + 1, upper, value);
	}

	return index;

}