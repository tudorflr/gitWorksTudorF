/**
* @author Florea Tudor
* @group 30425
*
* lab5 - Merge K lists
*
* ex1 I made a somewhat inefficient algorithm which compares all the first elements at every step
* 
* ex2 adapted the min heap to get a O(n log k)
* 
* ex3 for k=5 and k=10 it is pretty similar, but for k=100 it becomes much more inefficient
* 
* for a constant n, as the k goes higher and higher it becomes more inefficient
*
*/


#include <iostream>
#include "Profiler.h"

Profiler p("lab04");

using namespace std;


typedef struct node {
    int number;
    struct node *next;
}NodeT;


NodeT* create(int number) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if (!newNode) {
        cout << "nana";
        exit(-1);
    }
    newNode->next = NULL;
    newNode->number = number;
    return newNode;
}


NodeT* insertList(NodeT *first,int number) {
    if (first == NULL) {
        return create(number);
    }
    else {
        first->next = insertList(first->next, number);
        return first;
    }
}


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


void minHeapify(NodeT* arr[], int n, int i, int graphSize) {
    Operation ops = p.createOperation("mergeK", graphSize);
    int leftElement = left(i);
    int rightElement = right(i);
    int smallM = i;

    ops.count();
    if (leftElement < n && arr[leftElement]->number < arr[i]->number) {
        smallM = leftElement;
    }
    ops.count();
    if (rightElement < n && arr[rightElement]->number < arr[smallM]->number) {
        smallM = rightElement;
    }

    if (smallM != i) {
        ops.count(3);
        swap(arr[i], arr[smallM]);
        minHeapify(arr, n, smallM, graphSize);
    }
}


void buildHeapBU(NodeT* arr[], int n, int graphSize) {
    int len, i;
    len = n;
    for (i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i, graphSize);
    }
}


void mergingListsWHeap(NodeT* ListA[], int k, int graphSize, int showYxN) {
    Operation ops = p.createOperation("mergeK", graphSize);
    NodeT* result = NULL;
    int countForSize = k, i;

    buildHeapBU(ListA, k, graphSize);

    while (countForSize > 0) {
        ops.count(2);
        result = insertList(result, ListA[0]->number);
        ListA[0] = ListA[0]->next;  

        ops.count();
        if (ListA[0] == NULL) {
            countForSize--;
            ListA[0] = ListA[countForSize];
            ops.count();
        }
        minHeapify(ListA, countForSize, 0, graphSize);
    }

    if (showYxN == 1) {
        while (result->next != NULL) {
            cout << result->number << " ";   // aici afisez
            result = result->next;
        }
        cout << result->number;
    }
    
}


void listMerge(NodeT* ListA[], int n, int k) {
    int i = 0, j, min, minIndex;
    while (i < n) {
        min = 100000;
        for (j = 1; j <= k; j++) {
            if (ListA[j] != NULL && ListA[j]->number < min) {    // asta i time complexity O(n * k) cred
                min = ListA[j]->number;
                minIndex = j;
            }
        }
        ListA[0] = insertList(ListA[0], ListA[minIndex]->number);   // merge un if != NULL da e mai complex asa i guess
        ListA[minIndex] = ListA[minIndex]->next;    // s ar putea sa se futa ca primeste null
        i++;
    }
}


void printLists(NodeT* ListA[], int k) {
    int i;
    for (i = 0; i <= k; i++) {
        NodeT* aux = ListA[i];
        cout << "List " << i << " : ";
        if (aux == NULL) {
            cout << "empty";
        }
        else {
            while (aux->next != NULL) {
                cout << aux->number << " ";
                aux = aux->next;
            }
            cout << aux->number;
        }
        cout << endl;
    }
}


void transArrList(NodeT* ListA[], int a[], int n, int k) {    // vreau sa l chem cu 2
    int i, div, divcnt = 0, listCnt = 1;

    div = n / k;

    for (i = 0; i < n; i++) {
        if (divcnt < div) {
            ListA[listCnt] = insertList(ListA[listCnt], a[i]);
            divcnt++;
        }
        else {
            divcnt = 1;
            listCnt++;
            ListA[listCnt] = insertList(ListA[listCnt], a[i]);
        }
    }

}


void transArrListV2(NodeT* ListA[], int a[], int n, int k) {
    int i, div, divcnt = 0, listCnt = 0;

    div = n / k;

    for (i = 0; i < n; i++) {
        if (divcnt < div) {
            ListA[listCnt] = insertList(ListA[listCnt], a[i]);
            divcnt++;
        }
        else {
            divcnt = 1;
            listCnt++;
            ListA[listCnt] = insertList(ListA[listCnt], a[i]);
        }
    }

}


void demoTransf(NodeT* ListA[]) {
    int a[15] = { 1,5,7,9,12,8,19,20,21,25,2,6,19,27,30 };

    transArrList(ListA, a, 15, 3);
    /*
    ListA[1] = insertList(ListA[1], 10);
    ListA[1] = insertList(ListA[1], 18);

    ListA[2] = insertList(ListA[2], 1);
    ListA[2] = insertList(ListA[2], 8);

    ListA[2] = insertList(ListA[2], 29);
    */

    cout << "before merge : " << endl;
    printLists(ListA, 3);

    listMerge(ListA, 15, 3);

    cout << "after merge : " << endl;
    //printLists(ListA, 0);

    while (ListA[0]->next != NULL) {
        cout << ListA[0]->number << " ";
        ListA[0] = ListA[0]->next;
    }
    cout << ListA[0]->number;
}


void demoHeapMerge(NodeT* ListA[]) {
    cout << endl;
    int a[15] = { 1,5,7,9,12,16,19,20,21,25,2,6,19,27,30 };
    int f;
    for (f = 0; f <= 3; f++) {
        ListA[f] = NULL;
    }

    transArrListV2(ListA, a, 15, 3);

    cout << "before merge : " << endl;
    printLists(ListA, 3);

    cout << "after merge : ";
    mergingListsWHeap(ListA, 3, 15, 1);

}


void demoLists(NodeT* ListA[], int k) {
    int i;

    ListA[0] = insertList(ListA[0], 10);
    ListA[0] = insertList(ListA[0], 18);

    ListA[1] = insertList(ListA[1], 1);
    ListA[1] = insertList(ListA[1], 8);
 
    ListA[0] = insertList(ListA[0], 29);

    ListA[1] = insertList(ListA[1], 15);

    for (i = 0; i < k; i++) {
        cout << "List " << i << " : ";
     //   printList(ListA[i], 2);
        cout << endl;
    }

}


void transformRandom(NodeT* ListA[], int n, int k) {
    int i=0, ok=0,b[1000], sumEl=0, j;  // b - size of each list

    FillRandomArray(b, k, 10, 100, false, 0);
    
    for (i = 0; i < k; i++) {
        sumEl = b[i] + sumEl;
    }

    int divCnt = 0;
    while (sumEl < n) {
        b[divCnt] = b[divCnt] + 1;
        sumEl = 0;
        for (i = 0; i < k; i++) {
            sumEl = b[i] + sumEl;
        }
        divCnt++;
        if (divCnt == k) {
            divCnt = 0;
        }
    }

    sumEl = 0;
    for (i = 0; i < k; i++) {
        sumEl = b[i] + sumEl;
    }
    divCnt = 0;

    while (sumEl > n) {
        if (b[divCnt] > 1) {
            b[divCnt] = b[divCnt] - 1;
        }
        sumEl = 0;
        for (i = 0; i < k; i++) {
            sumEl = b[i] + sumEl;
        }
        divCnt++;
        if (divCnt == k) {
            divCnt = 0;
        }
    }

    sumEl = 0;

    /*
    for (i = 0; i < k; i++) {
        cout << b[i] << " ";
    }
    */

    int auxArr[1000];
    for (i = 0; i < k; i++) {
        FillRandomArray(auxArr, b[i], 10, 10000, false, 1);
        for (j = 0; j < b[i]; j++) {
            ListA[i] = insertList(ListA[i], auxArr[j]);
        }
    }

    //printLists(ListA, k);

}


void perfMergeK(int order, int k) {
    NodeT* ListA[1000];
    int f;
    for (f = 0; f <= k; f++) {
        ListA[f] = NULL;
    }
    int a[1000];
    int n, i, j;

    for (n = 100; n <= 1000; n += 100) {
            for (f = 0; f <= k; f++) {
                ListA[f] = NULL;
            }
            transformRandom(ListA, n, k);

            mergingListsWHeap(ListA, k, n, 0);
    }

    //p.createGroup("Comparison - Heap & QuickSort", "quickSort-ops", "heapBU-operations");

    //p.showReport();
}


void perfMergeAllwNvary() {
    perfMergeK(0, 5);
    p.reset("k=10");
    perfMergeK(0, 10);
    p.reset("k=100");
    perfMergeK(0, 100);
    p.reset("next");
}


void perfMergeKvary() {
    NodeT* ListA[1000];
    int f, k;
    int a[1000];
    int n = 1000, i, j;

    for (k = 10; k <= 500; k += 10) {
        for (f = 0; f <= k; f++) {
            ListA[f] = NULL;
        }
        transformRandom(ListA, n, k);

        mergingListsWHeap(ListA, k, k, 0);
    }

}


int main()
{
    int i;
    int k = 100;

    NodeT* ListA[1000];

    for (i = 0; i <= k; i++) {
        ListA[i] = NULL;
    }

    //demoLists(ListA, k);

    demoTransf(ListA);            //   asta momentan nu merge pe sized diferit

    demoHeapMerge(ListA);

    //transformRandom(ListA, 100, 3);  // test pt mn

    perfMergeAllwNvary();

    perfMergeKvary();

    p.reset("end");

    return 0;
}
