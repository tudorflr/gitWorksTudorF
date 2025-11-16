/**
* @author Florea Tudor
* @group 30425
*
* Bubble sort rec <> iter
*
*  They have the same nr of assignments and comparisons but the recursive one takes longer to process
*
* 
* Heap down up and top down comparison
* 
* BU is more efficient with a simpler time complexity than BD
* 
* 
* Worst case
* 
* Top down is much worse than bottom up
* 
* 
*/



#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler p("lab02");

void bubbleRec(int a[], int n, int opsize) {

	Operation opComp = p.createOperation("bubblesortRec-comp", opsize);
	Operation opAttr = p.createOperation("bubblesortRec-attr", opsize);

	int i,swapcnt=0;

	for (i = 0; i < n - 1; i++) {
		opComp.count();
		if (a[i] > a[i + 1]) {
			opAttr.count(3);
			swap(a[i], a[i + 1]);
			swapcnt++;
		}
	}
	if (swapcnt == 0) {
		return;
	}
	if (n > 0) {
		bubbleRec(a, n - 1, opsize);
	}
}


void bubblesort(int a[100], int n) {
	Operation opComp = p.createOperation("bubblesort-comp", n);
	Operation opAttr = p.createOperation("bubblesort-attr", n);
	int i, j, ok = 1, nrofproc = 0;
	for (i = 0; i < n; i++) {
		ok = 0;
		for (j = 0; j < n - i - 1; j++) {
			opComp.count();
			if (a[j] > a[j + 1]) {
				opAttr.count(3);
				swap(a[j], a[j + 1]);
				ok = 1;
			}
		}
		if (ok == 0) {
			break;
		}
	}
}


void displayArray(int a[100], int n) {
	int i;
	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}


void perfBubble(int order) {
	int a[1000],b[1000],c[1000],d[1000];
	int n, i, j;

	for (n = 100; n <= 1000; n += 100) {
		for (i = 0; i < 10; i++) {
			FillRandomArray(a, n, 10, 50000, false, order);
			for (j = 0; j < n; j++) {
				b[j] = a[j];
				c[j] = a[j];
				d[j] = a[j];
			}
			bubbleRec(a, n, n);
			bubblesort(b, n);
		}

		p.startTimer("bubbleRecTime", n);
		for (int test = 0; test < 1000; ++test) {
			bubbleRec(c, n, n);
		}
		p.stopTimer("bubbleRecTime", n);
														 // for time
		p.startTimer("bubbleTime", n);
		for (int test = 0; test < 1000; ++test) {
			bubblesort(d, n);
		}
		p.stopTimer("bubbleTime", n);

	}

	p.divideValues("bubblesortRec-attr", 10);  //  numar de teste
	p.divideValues("bubblesortRec-comp", 10);
	p.divideValues("bubblesort-attr", 10);
	p.divideValues("bubblesort-comp", 10);

	p.createGroup("bubbleDiff-att", "bubblesortRec-attr", "bubblesort-attr");
	p.createGroup("bubbleDiff-comp", "bubblesortRec-comp", "bubblesort-comp");

	p.createGroup("bubbleDiff-Time", "bubbleRecTime", "bubbleTime");

	//p.createGroup("Number of OP", "bubblesort-attr", "bubblesort-comp");

	p.showReport();


}



void demoBubble() {
	int a[100] = { 54, 29, 93, 1, 15, 66, 72, 45, 89, 10,
				  37, 5, 84, 22, 67, 99, 12, 76, 47, 61,
				  50, 28, 16, 34, 91, 40, 6, 80, 77, 3,
				  57, 70, 38, 81, 11, 32, 26, 85, 62, 31,
				  48, 24, 71, 17, 8, 18, 43, 98, 75, 36,
				  63, 13, 30, 56, 86, 64, 21, 4, 14, 79,
				  95, 7, 58, 83, 2, 25, 53, 42, 23, 27,
				  90, 20, 74, 39, 35, 82, 68, 87, 46, 65,
				  9, 33, 55, 100, 52, 19, 44, 60, 78, 73,
				  41, 49, 59, 88, 92, 94, 69, 51, 97, 96 };
	bubbleRec(a, 100, 69);
	displayArray(a, 100);
}


     // ex 2



int left(int i) {
	int child;
	child = 2 * i + 1;
	return child;
}

int right(int i) {
	int child;
	child = 2 * i + 2;
	return child;
}


void maxHeapify(int arr[], int n, int i, int graphSize) {
	Operation ops = p.createOperation("heapBU-operations", graphSize);

	int leftElement, rightElement, largest;
	leftElement = left(i);
	rightElement = right(i);
	largest = i;
	ops.count();
	if (leftElement < n && arr[leftElement] > arr[i]) {
		largest = leftElement;
	}
	ops.count();
	if (rightElement < n && arr[rightElement] > arr[largest]) {
		largest = rightElement;
	}
	if (largest != i) {
		ops.count(3);
		swap(arr[i], arr[largest]);
		maxHeapify(arr, n, largest, graphSize);
	}
}


void buildMaxHeapBU(int arr[], int n, int graphSize) {
	int len, i;
	len = n;
	for (i = n / 2 - 1; i >= 0; i--) {
		maxHeapify(arr, n, i, graphSize);
	}
}


void Heap(int arr[], int n) {
	int i;
	buildMaxHeapBU(arr, n, 69);
	for (i = n - 1; i > 0; i--) {		// n - size
		swap(arr[0], arr[i]);
		maxHeapify(arr, i, 0, 69);
	}
}


void demoHeapBU() {
	int test[7] = { 24,52,1,64,42,12,10 };
	buildMaxHeapBU(test, 7, 69);
	cout << "\nBottom up:";
	displayArray(test, 7);

	int testS[7] = { 24,52,1,64,42,12,10 };
	Heap(testS, 7);
	cout << "\n" << "Heap sort with BU:";
	displayArray(testS, 7);
}


//Top-down


int heapExtractMax(int arr[], int n) {
	int max;
	max = arr[0];
	arr[0] = arr[n];    // nu folosesc
	maxHeapify(arr, n-1, 0, 69);
	return max;
}


int parent(int i) {
	return (i - 1) / 2;
}

void heapIncreaseKey(int arr[], int i, int key, int graphSize) {
	Operation ops = p.createOperation("heapTD-operations", graphSize);
	ops.count();
	if (key < arr[i])
	{
		return;
	}
	ops.count();
	arr[i] = key;
	ops.count();
	while (i > 0 && arr[parent(i)] < arr[i]) {
		ops.count(3);
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}

void maxHeapInsert(int arr[], int& heapSize, int key, int graphSize) {
	Operation ops = p.createOperation("heapBU-operations", graphSize);
	heapSize++;
	arr[heapSize - 1] = -1;
	ops.count();
	heapIncreaseKey(arr, heapSize - 1, key, graphSize);
}

void buildMaxHeapTD(int arr[], int n, int graphSize) {
	int heapSize = 0;
	for (int i = 0; i < n; i++) {
		maxHeapInsert(arr, heapSize, arr[i], graphSize);
	}
}

void demoHeapTD() {
	int test[7] = { 24, 52, 1, 64, 42, 12, 10 };
	buildMaxHeapTD(test, 7, 69);
	cout << "\nTop down: ";
	displayArray(test, 7);

	//int testS[7] = { 24, 52, 1, 64, 42, 12, 10 };
	// Heap(testS, 7);
	// cout << "\nHeap sort with TD: ";
	// displayArray(testS, 7);
}


void perfHeap(int order) {
	//p.reset("heap");
	int a[1000], b[1000];
	int n, i, j;

	for (n = 100; n <= 1000; n += 100) {
		for (i = 0; i < 10; i++) {
			FillRandomArray(a, n, 10, 50000, false, order);
			for (j = 0; j < n; j++) {
				b[j] = a[j];
			}
			buildMaxHeapBU(a, n, n);
			buildMaxHeapTD(b, n, n);
		}
	}

	p.divideValues("heapBU-operations", 10);  
	p.divideValues("heapTD-operations", 10);

	p.createGroup("Heapify, comparison", "heapBU-operations", "heapTD-operations");

	p.showReport();
}


void worstCaseHeap(int order) {
	//p.reset("worst");
	int a[1000], b[1000];
	int n, i, j;

	for (n = 100; n <= 1000; n += 100) {
		for (i = 0; i < 10; i++) {
			FillRandomArray(a, n, 10, 50000, false, order);
			for (j = 0; j < n; j++) {
				b[j] = a[j];
			}
			buildMaxHeapBU(a, n, n);
			buildMaxHeapTD(b, n, n);
		}
	}

	p.divideValues("heapBU-operations", 10);
	p.divideValues("heapTD-operations", 10);

	p.createGroup("Heapify, comparison worst case", "heapBU-operations", "heapTD-operations");

	p.showReport();
}


int main()
{
	demoBubble();
	 
	perfBubble(0);

	demoHeapBU();
	demoHeapTD();

	perfHeap(0);
	worstCaseHeap(1); // 1 for order
	return 0;
}
