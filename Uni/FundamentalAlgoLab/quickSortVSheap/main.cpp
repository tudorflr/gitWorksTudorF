/**
* @author Florea Tudor
* @group 30425
*
* lab4 - quicksort vs heap etc.
*
* QuickSort on average and best has same as O(n log n) but worst has O(n^2)
*  
* Quicksort vs heapsort
* 
* Has same complexity in best and avearage but worst is much worse in quicksort, 
* but average usually gives out better results
* 
* Quicksort hybrid
* 
* I determined that threshold 5 is best for nr of operations, but 15 is better for
* time complexity and as for the comparison with thr 5 quicksort is a bit faster for
* operations but slower in time
* 
* 
*/


#include <iostream>
#include "Profiler.h"

Profiler p("lab03");

using namespace std;


int part(int a[], int left, int right, int arrSize) {
    Operation ops = p.createOperation("quickSort-ops", arrSize);
    int x, i, j;
    ops.count();
    x = a[right];
    i = left - 1;
    for (j = left; j <= right - 1; j++) {
        ops.count();
        if (a[j] < x) {
            i++;
            ops.count(3);
            swap(a[i], a[j]);
        }
    }
    ops.count(3);
    swap(a[i + 1], a[right]);
    return i + 1;
}


void quickSort(int a[], int left, int right, int arrSize) {
    int divSpot;
    if (left < right) {
        divSpot = part(a, left, right, arrSize);
        quickSort(a, left, divSpot - 1, arrSize);
        quickSort(a, divSpot + 1, right, arrSize);
    }
}


void displayArray(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}


// Heap Sort
 

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
    buildMaxHeapBU(arr, n, n);
    for (i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0, n);
    }
}


// QuickSort Hybrid


void insertionsort(int a[], int n , int left, int right) {
    Operation ops = p.createOperation("quickSortH-ops", n);
    int i, j;
    for (i = left + 1; i <= right; i++) {   // nu inteleg inca de ce left + 1 trb sa inteleg
        j = i;
        while (a[j] < a[j - 1] && j > left) {
            ops.count();
            ops.count(3);
            swap(a[j], a[j - 1]);
            j--;
        }
    }
}


int partH(int a[], int left, int right, int arrSize) {
    Operation ops = p.createOperation("quickSortH-ops", arrSize);
    int x, i, j;
    ops.count();
    x = a[right];
    i = left - 1;
    for (j = left; j <= right - 1; j++) {
        ops.count();
        if (a[j] < x) {
            i++;
            ops.count(3);
            swap(a[i], a[j]);
        }
    }
    ops.count(3);
    swap(a[i + 1], a[right]);
    return i + 1;
}


void quickSortH(int a[], int left, int right, int arrSize, int thr) {
    int divSpot;
    if (left < right - thr) {
        divSpot = partH(a, left, right, arrSize);
        quickSortH(a, left, divSpot - 1, arrSize, thr);
        quickSortH(a, divSpot + 1, right, arrSize, thr);
    }
    else {
        insertionsort(a, arrSize, left, right);
    }
}


void bestCase(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    swap(a[right], a[mid]);

    bestCase(a, left, mid - 1);
    bestCase(a, mid + 1, right - 1);
}


void perfQS(int order, int cases) {
    //p.reset("heap");
    if (cases == 0) {
        int a[1000];
        int n, i, j;

        for (n = 100; n <= 1000; n += 100) {
            for (i = 0; i < 10; i++) {
                FillRandomArray(a, n, 10, 50000, false, order);
                quickSort(a, 0, n - 1, n);
            }
        }

        p.divideValues("quickSort-ops", 10);
    }
    else {
        int a[1000];
        int n, i, j;

        for (n = 100; n <= 1000; n += 100) {
            for (i = 0; i < 10; i++) {
                FillRandomArray(a, n, 10, 50000, false, order);

                bestCase(a,0,n-1);

                quickSort(a, 0, n - 1, n);
            }
        }

        p.divideValues("quickSort-ops", 10);
    }
}


void perfAllQS() {
    perfQS(0, 0);
    p.reset("worst");
    perfQS(1, 0);
    p.reset("best");
    perfQS(1, 1);
}


void demoQS() {
    int a[50] = {
    34, 78, 56, 12, 89, 90, 23, 67, 45, 82,
    91, 3, 15, 76, 50, 99, 31, 27, 61, 44,
    18, 73, 85, 26, 37, 49, 92, 10, 62, 84,
    54, 7, 63, 30, 25, 93, 66, 1, 47, 39,
    13, 22, 58, 88, 75, 2, 41, 35, 69, 53
    };
    quickSort(a, 0, 49, 50);
    cout << "QuickSort demo : ";
    displayArray(a, 50);
}


void perfComparisonHeapQuick(int order) {
    int a[1000], b[1000];
    int n, i, j, k;

    p.reset("Heap vs Quick");

    for (n = 100; n <= 1000; n += 100) {
        for (i = 0; i < 10; i++) {
            FillRandomArray(a, n, 10, 50000, false, order);

            for (k = 0; k < n; k++) {
                b[k] = a[k];
            }

            quickSort(a, 0, n - 1, n);
            Heap(b, n);
        }
    }

    p.divideValues("quickSort-ops", 10);
    p.divideValues("heapBU-operations", 10);

    p.createGroup("Comparison - Heap & QuickSort", "quickSort-ops", "heapBU-operations");

    //p.showReport();
}


void perfQHSdetTHR(int order) {
    int a[1000], b[1000];
    int n, i, j, k;

    p.reset("QHSdetTHR");

    for (n = 5; n <= 50; n += 5) {
        for (i = 0; i < 10; i++) {
            FillRandomArray(a, 1000, 10, 50000, false, order);

            for (k = 0; k < n; k++) {
                b[k] = a[k];
            }

            quickSortH(a, 0, 1000 - 1, n, n); // threshold 


        }

        p.startTimer("quickSortH - time", n);
        for (int test = 0; test < 100; ++test) {
            quickSortH(b, 0, 1000 - 1, n, n);
        }
        p.stopTimer("quickSortH - time", n);

    }


    p.divideValues("quickSortH-ops", 10);

    //p.showReport();
}


void perfQHScomp(int order) {
    int a[1000], b[1000], c[1000], d[1000];
    int n, i, j, k;

    p.reset("QHScmp");

    for (n = 100; n <= 1000; n += 100) {
        for (i = 0; i < 10; i++) {
            FillRandomArray(a, n, 10, 50000, false, order);

            for (k = 0; k < n; k++) {
                b[k] = a[k];
                c[k] = a[k];
                d[k] = a[k];
            }

            quickSort(a, 0, n - 1, n);
            quickSortH(b, 0, n - 1, n, 5); // threshold    -- pt 10 - H e putin mai eficient , 5 pare ideal
        }

        p.startTimer("quickSort - time", n);
        for (int test = 0; test < 100; ++test) {
            quickSort(c, 0, n - 1, n);
        }
        p.stopTimer("quickSort - time", n);

        p.startTimer("quickSortHy - time", n);
        for (int test = 0; test < 100; ++test) {
            quickSortH(d, 0, n - 1, n, 10);
        }
        p.stopTimer("quickSortHy - time", n);

    }

    p.divideValues("quickSort-ops", 10);
    p.divideValues("quickSortH-ops", 10);

    p.createGroup("Comparison - QuickSort & Hybrid", "quickSort-ops", "quickSortH-ops");
    p.createGroup("Comparison - QuickSort & Hybrid - Time", "quickSort - time", "quickSortHy - time");


    //p.showReport();
}


void demoQSH() {
    int a[50] = {
    34, 78, 56, 12, 89, 90, 23, 67, 45, 82,
    91, 3, 15, 76, 50, 99, 31, 27, 61, 44,
    18, 73, 85, 26, 37, 49, 92, 10, 62, 84,
    54, 7, 63, 30, 25, 93, 66, 1, 47, 39,
    13, 22, 58, 88, 75, 2, 41, 35, 69, 53
    };

    quickSortH(a, 0, 49, 50, 10); // ultimul parametru e threshold

    cout << endl;
    cout << "QuickSort Hybrid demo : ";
    displayArray(a, 50);

}


int main()
{
    demoQS();
    perfAllQS();

    perfComparisonHeapQuick(0);

    demoQSH();
    perfQHSdetTHR(0);
 
    perfQHScomp(0);

    p.reset("end");

    return 0;
}