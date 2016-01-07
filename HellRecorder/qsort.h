#ifndef QSORT_H
#define QSORT_H

/*
** I tried to implement quick sort but I kept getting seg faults.
** So I just resorted to using my previously made merge sort algorithm
*/



#include "arraylist.h"
#include "hellrun.h"

int partitionRun(ArrayList<Epic>& myList, int start, int end, int p);

int partitionName(ArrayList<Epic>& myList, int start, int end, int p);

// If type is false, indicates partitioning run. Else, partition by name
void quickSort(ArrayList<Epic>& myList, int start, int end, bool type);



#endif