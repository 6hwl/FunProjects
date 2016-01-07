#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include "arraylist.h"


template <class T, class Comparator>

void mergeSort (ArrayList<T>& myArray, Comparator comp) {
	msort(myArray, 0, myArray.size() - 1, comp);
}

template <class T, class Comparator>

void msort(ArrayList<T>& myArray, int start, int end, Comparator comp) {
	if (start >= end) return;

	int mid = (start + end) / 2;

	msort(myArray, start, mid, comp);
	msort(myArray, mid + 1, end, comp);

	merge(myArray, start, mid, end, comp);
}

template <class T, class Comparator>

void merge(ArrayList<T>& myArray, int start, int mid, int end, Comparator comp) {
	ArrayList<T> temp;
	int i = start;
	int j = mid + 1;

	while (i <= mid || j <= end) {
		if (i <= mid && (j > end || comp(myArray[i], myArray[j]))) {
			temp.insert(temp.size(), myArray[i]);
			i++;
		} else {
			temp.insert(temp.size(), myArray[j]);
			j++;
		}
	}

	for (unsigned int k = 0; k < temp.size(); k++) {
		myArray[k + start] = temp[k];
	}
}

#endif