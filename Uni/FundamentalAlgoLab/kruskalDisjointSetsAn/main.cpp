/**
* @author Florea Tudor Dan
* @group 30425
*
* lab08 - Disjoint Sets
*
*   Make sets all the nodes, and initially the nodes parent is himself
*   Find finds the root baisically, the one with biggest rank
*   Union + Link finds the root of 2 subtrees, if it is the same 
*   then nothing has to be done since they are linked, if not 
*   it links the root with to lower rank to the other.
*
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Profiler.h"

Profiler p("lab08");

using namespace std;

typedef struct Node {
    int parent;
    int rank;
} NodeT;


typedef struct Edge {
    int start;
    int dest;
    int weight;
} EdgeT;


void MakeSet(NodeT* nodes[], int x, int testSize) {
    Operation opsMake = p.createOperation("TotalOperations - Make Set", testSize);
    opsMake.count(3);
    nodes[x] = new NodeT();
    nodes[x]->parent = x;
    nodes[x]->rank = 0;
}


int Find(NodeT* nodes[], int x, int testSize) {
    Operation opsFind = p.createOperation("TotalOperations - Find", testSize);
    opsFind.count();
    if (nodes[x]->parent != x) {
        opsFind.count();
        nodes[x]->parent = Find(nodes, nodes[x]->parent, testSize); 
    }
    return nodes[x]->parent;
}


void Link(NodeT* nodes[], int x, int y, int testSize) {
    Operation opsUnion = p.createOperation("TotalOperations - Union", testSize);
    opsUnion.count(); // for actual Union fct
    //opsUnion.count();
    if (x != y) {
        opsUnion.count();
        if (nodes[x]->rank > nodes[y]->rank) {
            opsUnion.count();
            nodes[y]->parent = x;
        }
        else if (nodes[x]->rank < nodes[y]->rank) {
            opsUnion.count();
            nodes[x]->parent = y;
        }
        else {
            opsUnion.count(2);
            nodes[y]->parent = x;
            nodes[x]->rank++;
        }
    }
}


void Union(NodeT* nodes[], int x, int y, int testSize) {
    int rootX = Find(nodes, x, testSize);
    int rootY = Find(nodes, y, testSize);

    if (rootX != rootY) {
        Link(nodes, rootX, rootY, testSize);
    }
}


void sortSimple(EdgeT* edges[], int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j]->weight > edges[j + 1]->weight) {
                EdgeT* aux = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = aux;
            }
        }
    }
}


static void Kruskal(EdgeT* edges[], int edgeCount, int nodeCount, int testSize, int print) {
    NodeT* nodes[10000];
    EdgeT* finalG[10000];
    int finalGIndex = 0;

    for (int i = 0; i < nodeCount; i++) {
        MakeSet(nodes, i, testSize);
    }

    sortSimple(edges, edgeCount);

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i]->start;
        int v = edges[i]->dest;

        if (Find(nodes, u, testSize) != Find(nodes, v, testSize)) {
            finalG[finalGIndex++] = edges[i];
            Union(nodes, u, v, testSize);
        }

        if (finalGIndex == nodeCount - 1) {
            break;
        }
    }

    if (print == 1) {
        cout << endl;
        cout << "Krusky" << endl;
        for (int i = 0; i < finalGIndex; i++) {
            cout << finalG[i]->start << " -- " << finalG[i]->dest << " == " << finalG[i]->weight << endl;
        }
    }

    
    for (int i = 0; i < nodeCount; i++) {
        delete nodes[i];
    }
    /*
    for (int i = 0; i < finalGIndex; i++) {
        delete finalG[i];
    }
    */
    
}


void DemoEx1() {
    int i, j;
    NodeT* nodeTest[100];
    MakeSet(nodeTest, 0, 5);
    MakeSet(nodeTest, 1, 5);
    MakeSet(nodeTest, 2, 5);
    MakeSet(nodeTest, 3, 5);
    MakeSet(nodeTest, 4, 5);
    MakeSet(nodeTest, 5, 5);
    MakeSet(nodeTest, 6, 5);
    MakeSet(nodeTest, 7, 5);
    MakeSet(nodeTest, 8, 5);
    MakeSet(nodeTest, 9, 5);

    Union(nodeTest, 1, 3, 5);
    Union(nodeTest, 1, 7, 5);
    Union(nodeTest, 2, 5, 5);
    Union(nodeTest, 2, 1, 5);
    Union(nodeTest, 6, 1, 5);

    for (i = 0; i < 10; i++) {
        cout << endl;
        cout << " Children of " << i << " : ";
        for (j = 0; j < 10; j++) {
            if (nodeTest[j]->parent == i) {
                cout << j << " ";
            }
        }
    }
    
    cout << endl;
    for (i = 0; i < 10; i++) {
        cout << endl;
        cout << i << " : ''Luke I am ur father'' : (said to) " << nodeTest[i]->parent << " ";
    }

}


void DemoEx2() {
    int i;
    int nodeCount = 5;  // trb schimbat din 6
    int edgeCount = 9;

    EdgeT* edges[100] = {
        new EdgeT{0, 1, 4}, new EdgeT{0, 2, 1}, new EdgeT{1, 2, 2}, new EdgeT{1, 0, 4},
        new EdgeT{2, 3, 3}, new EdgeT{2, 4, 2}, new EdgeT{2, 0, 1}, new EdgeT{3, 4, 3},
        new EdgeT{1, 4, 3}
    };

    for (i = 0; i < 9; i++) {
        cout << endl;
        cout << edges[i]->start << " -----> " << edges[i]->dest << " with weight : " << edges[i]->weight;
    }

    Kruskal(edges, edgeCount, nodeCount, 6 , 1);

    /*
    for (int i = 0; i < edgeCount; i++){
        delete edges[i];
    }
    */
}

void PerfAll() {
    int testSizeNode; // i
    int testSizeEdges;
    int i, j, randomNr;
    EdgeT* edges[50000];

    srand(time(NULL));

    for (i = 100; i <= 5000; i = i + 100) {

        for (j = 0; j < i * 4; j++) {
            edges[j] = new EdgeT();
        }

        edges[0]->start = rand() % 10;
        edges[0]->dest = rand() % 10; // primu e la fel asa doar
        edges[0]->weight = rand() % 100;
        edges[1]->start = 0;
        edges[1]->dest = 1;
        edges[1]->weight = rand() % 100;
        for (j = 2; j < i; j++) {
            randomNr = rand() % j; 
            edges[j]->start = randomNr;
            randomNr = rand() % j; 
            edges[j]->dest = randomNr;
            randomNr = rand() % 10000; 
            edges[j]->weight = randomNr;
        }

        for (j = i; j < i * 4; j++) {
            randomNr = rand() % i;
            edges[j]->start = randomNr;
            randomNr = rand() % i;
            edges[j]->dest = randomNr;
            randomNr = rand() % 10000;
            edges[j]->weight = randomNr;
        }

        testSizeEdges = i * 4;
        Kruskal(edges, testSizeEdges, i, i, 0);

        for (j = 0; j < testSizeEdges; j++) {
            delete edges[j];
        }
    }

    p.createGroup("All Operations", "TotalOperations - Make Set", "TotalOperations - Find", "TotalOperations - Union");

    p.showReport();
}


int main() {

    DemoEx1();

    DemoEx2();

    PerfAll();

    return 0;
}
