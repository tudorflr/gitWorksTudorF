/**
* @author Florea Tudor
* @group 30425
*
* lab5 - Hash Tables
*
* As the fill factor goes up, the search operation will be 
* more and more complex in nr. of operations, beacause it
* has to go trhrough more elements to get to the one that
* we are looking for, with the quadratic formula.
* 
* For an element which wont be found in the hash table,
* if we search for it the nr. of operations will be the same
* for the same fill facotor, beacuse it has to go through all
* the elements which aren't NULL.
* 
* For delete we can't set it back to NULL, because it will
* screw with the search function.
* 
*/

#include <iostream>
#include "Profiler.h"

Profiler p("lab05");

using namespace std;

typedef struct node {
    int number;
}NodeT;


NodeT* create(int number) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if (!newNode) {
        cout << "nana";
        exit(-1);
    }
    newNode->number = number;
    return newNode;
}


void resetHashT(NodeT* ListA[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        ListA[i] = NULL;
    }
}


int calculatePos(int number, int i, int n) {
    int h0 = number % n;  
    int c1 = 1, c2 = 5, c3 = 7;  
    return (c1 * i * i + c2 * i + c3 + h0) % n; 
}


int insert(NodeT* ListA[], int number, int n) {
    int i, pos;
    for (i = 0; i < n; i++) {
        pos = calculatePos(number, i, n);
        if (ListA[pos] == NULL || (ListA[pos] != NULL && ListA[pos]->number == -1)) {   // am modif conditia sa incerc delete nush daca merge momentan
            ListA[pos] = create(number);
            return 1;
        }
    }
    return 2;
}


int searchTest(NodeT* ListA[], int number, int n) {
    int i = 0, pos;
    pos = calculatePos(number, i, n);
    while (i < n && ListA[pos] != NULL) {
        pos = calculatePos(number, i, n);
        if (ListA[pos] != NULL && ListA[pos]->number == number) {
            cout << "found - " << number << endl;     
            return i;
        }
        i++;
    }
    cout << "couldnt find - " << number << endl;
    return i;
}


int search(NodeT* ListA[], int number, int n) {
    int i=0, pos;
    pos = calculatePos(number, i, n);
    while(i<n && ListA[pos] != NULL) {
        pos = calculatePos(number, i, n);
        if (ListA[pos] != NULL && ListA[pos]->number == number) {
            //cout << "found - " << number << endl;     // trb sa modif in while
            return i;
        }
        i++;
    }
    //cout << "couldnt find - " << number << endl;
    return i;
}


void printTable(NodeT* ListA[], int n) {
    int i;
    cout << "HashTable : ";
    for (i = 0; i < n; i++) {
        if (ListA[i] == NULL) {
            cout << "e ";
        }
        else {
            cout << (ListA[i]->number) << " ";
        }
    }
    cout << endl;
}


void deleteEl(NodeT* ListA[], int number, int n) {
    int i = 0, pos;
    pos = calculatePos(number, i, n);
    while (i < n && ListA[pos] != NULL) {
        pos = calculatePos(number, i, n);
        if (ListA[pos] != NULL && ListA[pos]->number == number) {
            ListA[pos]->number = -1;
        }
        i++;
    }
}


void transfArrINHash(NodeT* ListA[], int arr[], int fillPerc, int n, int arrSize, int visArr[]) {
    int stopAt, i, inserted=0, insertCnt = 0;
    stopAt = (fillPerc * n) / 100;
    i = 0;
    while (insertCnt < stopAt && i<arrSize) {
        inserted = insert(ListA, arr[i], n);
        i++;
        //cout << inserted << " ";
        if (inserted == 1) {
            insertCnt++;
            visArr[i] = 1;
        }
    }
    if (i >= arrSize ) {
        cout << "couldnt fill :(" << endl;
    }
}


void searchExistingAndNon(NodeT* ListA[], int randomizeArr[], int testArr[], int visArr[], int resultArr[]) {
    int i = 0, foundEl = 0, check = 0, nrOfSearch = 1500, nrOfSteps = 0;
    while (foundEl < nrOfSearch && i < 20000) { // nr of el that are in
        check = randomizeArr[i];
        if (visArr[check] == 1) {
            foundEl++;
            nrOfSteps = search(ListA, testArr[check], 9973);
            nrOfSteps++;    // pt ca for incepe de la 0 in functia search
            resultArr[foundEl] = nrOfSteps;
        }
        i++;
    }
      // astea care nu se gasesc sigur
    int stopsAt = 0;
    i = 0;
    while (stopsAt < nrOfSearch && i < 20000) {
        check = randomizeArr[i];
        if (visArr[check] == 0) {
            foundEl++;
            stopsAt++;
            nrOfSteps = search(ListA, testArr[check], 9973);
            nrOfSteps++;
            resultArr[foundEl] = nrOfSteps;
        }
        i++;
    }
}


void perfEx2(NodeT* ListA[], int fillFactor) {
    int arrSize=20000, i, cnt=0;
   // int testArr[30] = { 5, 1000, 10000, 10, 100, 42, 753, 211, 657, 1829, 503, 317, 2301, 994, 721, 1043, 15,
   //                     876, 340, 128, 587, 369, 204, 451, 998, 102, 333, 489, 214, 76 };
    int sum1 = 0, sum2 = 0, max1 = 0, max2 = 0, resultAll1=0,resultAll2=0;

    cout << fillFactor << "                    ";

    for (cnt = 0; cnt < 5; cnt++) {

        int testArr[20000], visArr[20000] = { 0 }, randomizeArr[20000], resultArr[5000] = { 0 };

        FillRandomArray(testArr, 20000, 10, 50000, false, 0);

        transfArrINHash(ListA, testArr, fillFactor, 9973, arrSize, visArr);  // set hash size of 1000

        FillRandomArray(randomizeArr, 20000, 0, 20000, true, 0);

        searchExistingAndNon(ListA, randomizeArr, testArr, visArr, resultArr);

        sum1 = 0; sum2 = 0;
        for (i = 0; i < 1500; i++) {
            sum1 = sum1 + resultArr[i];
            if (resultArr[i] > max1) {
                max1 = resultArr[i];      // gotta do the 5 tests, plus hash 10000
            }
        }
        for (i = 1500; i < 3000; i++) {
            sum2 = sum2 + resultArr[i];
            if (resultArr[i] > max2) {
                max2 = resultArr[i];
            }
        }
        sum1 = sum1 / 1500;
        sum2 = sum2 / 1500;
        resultAll1 = sum1 + resultAll1;
        resultAll2 = sum2 + resultAll2;
        resetHashT(ListA,9973);
    }

    cout << (resultAll1 / 5) << "               " << max1 << "               " << (resultAll2 / 5) << "            " << max2;  
}


void demoFirst(NodeT* ListA[]) {
    int n = 11;
    insert(ListA, 1001, n);
    insert(ListA, 102, n);
    insert(ListA, 100001, n);
    insert(ListA, 10001, n);
    insert(ListA, 1000001, n);

    searchTest(ListA, 102, n);
    searchTest(ListA, 103, n);
    searchTest(ListA, 1000001, n);


    printTable(ListA, n);
    resetHashT(ListA, n);
}


void perfAllFill(NodeT *ListA[]) {
    cout << "Fill factor     " << "Avg Eff found   " << "Max Eff found   " << "Avg Eff  not f  " << "Max Eff  not f  ";
    cout << endl;
    perfEx2(ListA, 80);
    resetHashT(ListA, 9973);
    cout << endl;
    perfEx2(ListA, 85);
    resetHashT(ListA, 9973);
    cout << endl;
    perfEx2(ListA, 90);
    resetHashT(ListA, 9973);
    cout << endl;
    perfEx2(ListA, 95);
    resetHashT(ListA, 9973);
    cout << endl;
    perfEx2(ListA, 99);
    resetHashT(ListA, 9973);
    cout << endl;
}


void demoDelete(NodeT* ListA[]) {
    int n = 11;
    insert(ListA, 1001, n);
    insert(ListA, 102, n);
    insert(ListA, 100001, n);
    insert(ListA, 10001, n);
    insert(ListA, 1000001, n);

    cout << "before delete : ";
    printTable(ListA, n);

    deleteEl(ListA, 10001, n);

    cout << "after delete : ";
    printTable(ListA, n);

    insert(ListA, 10001, n);
    cout << "after reinserting same el : ";
    printTable(ListA, n);

    resetHashT(ListA, n);
}


int main() 
{
    NodeT* ListA[10000];
    

    int i;
    for (i = 0; i < 10000; i++) {
        ListA[i] = NULL;
    }

    demoFirst(ListA); 

    //perfEx2(ListA, 95);

    perfAllFill(ListA);

    demoDelete(ListA);

}