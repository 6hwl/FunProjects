#ifndef QSORT_TEMPLATE_H
#define QSORT_TEMPLATE_H

#include "arraylist.h"

template <class T>
int partition(ArrayList<T> myList, int start, int end, int p) {
	int pivot = myList[p];
	myList.swap(p, end);

	int left = start;
	int right = end - 1;
	while (left < right) {
		while (myList[left] <= pivot && left < right)
			left++;
		while (myList[right] >= pivot && left < right)
			right++;
		if (left < right)
			myList.swap(left, right);
	}
	if (myList[right] > myList[end]) {
		myList.swap(right, end);
		return right;
	} else {
		return end;
	}
}


template <class T>
void quickSort(ArrayList<T>& myList, int start, int end) {
	if (start >= end) return;

	// Pick a random pivot location between start and end
	int p = start + rand() % (end + 1);
	// Partition
	int loc = partition(myList, start, end);
	// Recurse on both ends of myList
	qsort(myList, start, loc - 1);
	qsort(myList, loc + 1, end);
}




#endif