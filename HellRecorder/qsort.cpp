#include "qsort.h"
#include <iostream>

int partitionRun(ArrayList<Epic>& myList, int start, int end, int p) {
	int pivot = myList[p].runNumber;
	myList.swap(p, end);

	int left = start;
	int right = end - 1;
	while (left < right) {
		while (myList[left].runNumber <= pivot && left < right)
			left++;
		while (myList[right].runNumber >= pivot && left < right)
			right++;
		if (left < right)
			myList.swap(left, right);
	}
	if (myList[right].runNumber > myList[end].runNumber) {
		myList.swap(right, end);
		return right;
	} else {
		return end;
	}
}


int partitionName(ArrayList<Epic>& myList, int start, int end, int p) {
	std::string pivot = myList[p].name;
	myList.swap(p, end);

	int left = start;
	int right = end - 1;
	while (left < right) {
		while (myList[left].name <= pivot && left < right)
			left++;
		while (myList[right].name >= pivot && left < right)
			right++;
		if (left < right)
			myList.swap(left, right);
	}
	if (myList[right].name > myList[end].name) {
		myList.swap(right, end);
		return right;
	} else {
		return end;
	}
}



void quickSort(ArrayList<Epic>& myList, int start, int end, bool type) {
	if (start >= end) return;

	// Pick a random pivot location between start and end
	int p = rand() % end;
	std::cout << "End: " << end << std::endl;
	std::cout << "P: " << p << std::endl;
	// Partition
	int loc;
	if (type == false) loc = partitionRun(myList, start, end, p);
	else loc = partitionName(myList, start, end, p);
	// Recurse on both ends of myList
	quickSort(myList, start, loc - 1, type);
	quickSort(myList, loc + 1, end, type);
}
