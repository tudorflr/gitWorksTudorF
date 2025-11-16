/**
* @author Florea Tudor
* @group 30425
* 
* Sorting methods comparison
* 
*  Pentru atribuiri bubble si insertion sunt foarte asemanatoare spre deosebire de insertion care are mult mai putine in medie
*  Insertion are aproximativ jumatate din comparari fata de celelalte doua
*  Selection cum l am gandit eu are acelasi best worst si average
*  Insertion pe best are 0 operatii iar bubble are doar comparatii ce parcurg vectorul o data
*  
*/


#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler p("lab01");

void displaysorted(int a[100]) {
	int i;
	for (i = 0; i < 6; i++) {
		cout << a[i] << " ";
	}
}

void bubblesort(int a[100], int n) {
	Operation opComp = p.createOperation("bubblesort-comp", n);
	Operation opAttr = p.createOperation("bubblesort-attr", n);
	int i, j, ok = 1, nrofproc=0;
	for (i = 0; i < n; i++) {
		ok = 0;
		for (j = 0; j < n - i - 1  ; j++) {
			//nrofproc++;
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
	//cout << " " << nrofproc << " ";
}

void insertionsort(int a[100],int n) {
	Operation opComp = p.createOperation("insertionsort-comp", n);
	Operation opAttr = p.createOperation("insertionsort-attr", n);
	int i, j;
	for (i = 1; i < n - 1; i++) {
		j=i+1;
		while (a[j] < a[j-1] && j>0) {
			opComp.count();
			opAttr.count(3);
			swap(a[j], a[j - 1]);
			j--;
		}
	}
}

void selectionsort(int a[100],int n) {
	Operation opComp = p.createOperation("selectionsort-comp", n);
	Operation opAttr = p.createOperation("selectionsort-attr", n);
	int i, j, posj=0, nrofproc=0;
	for (i = 0; i < n; i++) {
		posj = i;
		for (j = i + 1 ; j < n; j++) {
			//nrofproc++;
			opComp.count();
			if (a[posj] > a[j]) {    // trb sa repar asta
				posj = j;
			}
		}
		opAttr.count(3);
		swap(a[i], a[posj]);
	}
	//cout << nrofproc;
}

void perf(int order) {
	int a[10000];
	int n;
	for (n = 100; n <= 1000; n += 100) {
		FillRandomArray(a, n, 10, 50000, false, order);
		bubblesort(a, n);
		FillRandomArray(a, n, 10, 50000, false, order);
		insertionsort(a, n);
		FillRandomArray(a, n, 10, 50000, false, order);
		selectionsort(a, n);
	}

	p.addSeries("bubblesort", "bubblesort-attr", "bubblesort-comp");
	p.addSeries("insertionsort", "insertionsort-attr", "insertionsort-comp");
	p.addSeries("selectionsort", "selectionsort-attr", "selectionsort-comp");

	p.createGroup("attr", "bubblesort-attr", "insertionsort-attr", "selectionsort-attr");
	p.createGroup("comp", "bubblesort-comp", "insertionsort-comp", "selectionsort-comp");

	p.createGroup("toatalop", "bubblesort", "insertionsort", "selectionsort");

}

void perf_all()
{
	perf(UNSORTED);
	p.reset("best");
	perf(ASCENDING);
	p.reset("worst");
	perf(DESCENDING);

	p.showReport();
}

int main() {
	//int a[7] = { 10,54,1,12,5,16,42 };

	//bubblesort(a,7);

	//insertionsort(a,7);

	//selectionsort(a,7);

	//displaysorted(a);

	perf_all();

	return 0;
}