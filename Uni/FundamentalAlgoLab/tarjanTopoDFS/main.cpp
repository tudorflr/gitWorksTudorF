/**
* @author Florea Tudor
* @group 30425
*
* lab10 - DFS
*
* DFS, is DFS
* 
* Topological search puts them in order of dependencies for oriented graphs
* 
* Tarjan finds the connected components
*
*/

#include <iostream>
#include <stack>
//#include "Profiler.h"

//Profiler p("lab10");


using namespace std;


typedef struct node {

    int key;
    int color;   // 0 - white  // 1 - grey  // 2 - black

    int time;  // DFS/topo
    int finishTime;  // DFS/topo

    int index = -1;     
    int lowlink = -1;   // tarjan
    bool onStack = false;
    int tarjanId = -1;   // for strong

    struct node* parent;
    struct node* links[10000];   // size not sure poate trb schimbat ulterior

}NodeT;


typedef struct graph {

    struct node* allNodes[1000]; // no sa ajunga sizeu

}GraphT;


NodeT* create(int key, GraphT* graph) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if (!newNode) {
        cout << "nana";
        exit(-1);
    }
    newNode->key = key;
    newNode->color = 0;  // initially white
    for (int i = 0; i < 10000; i++) {   // probabil o sa trebuiasca sa schimb asta ( pt perf )
        newNode->links[i] = NULL;
    }

    newNode->index = -1;
    newNode->lowlink = -1;
    newNode->onStack = false;
    newNode->tarjanId = -1;

    return newNode;
}


void addEdge(GraphT* graph, int startKey, int endKey) {
    NodeT* startNode = graph->allNodes[startKey];
    NodeT* endNode = graph->allNodes[endKey];

    for (int i = 0; i < 10000; i++) {
        if (startNode->links[i] == NULL) {
            startNode->links[i] = endNode;
            break;
        }
    }

    startNode = graph->allNodes[endKey];
    endNode = graph->allNodes[startKey];

    for (int i = 0; i < 10000; i++) {
        if (startNode->links[i] == NULL) {
            startNode->links[i] = endNode;
            break;
        }
    }

}

void addEdgeDir(GraphT* graph, int startKey, int endKey) {
    NodeT* startNode = graph->allNodes[startKey];
    NodeT* endNode = graph->allNodes[endKey];

    for (int i = 0; i < 30; i++) {
        if (startNode->links[i] == NULL) {
            startNode->links[i] = endNode;
            break;
        }
    }
}



void DFSVisit(GraphT* graph, NodeT* node, int& time, int print, stack<int>* topoS, int size) {
    //Operation ops = p.createOperation("TotalOperations - DFS", size);

    time++;
    node->time = time;
    node->color = 1; 
    //ops.count(2);
    if (print == 1) {   // doar pt print nu nr
        cout << node->key << " ";
    }

    int i = 0;
    while (node->links[i] != NULL) {
        //ops.count();
        NodeT* adjNode = node->links[i];
        //ops.count();
        if (adjNode->color == 0) {
            adjNode->parent = node;
            //ops.count();
            DFSVisit(graph, adjNode, time, print, topoS, size);
        }
        i++;
    }


    node->color = 2;
    time++;
    node->finishTime = time;

    if (topoS != nullptr) { // for topological only
        topoS->push(node->key);
    }
}

void DFS(GraphT* graph, int size, int print, int nrEdges) {
    //Operation ops = p.createOperation("TotalOperations - DFS", nrEdges);

    for (int i = 0; i < size; i++) {
        graph->allNodes[i]->color = 0; // set all nodes to white
        graph->allNodes[i]->parent = NULL;
        //ops.count(2);
    }
    int time = 0;

    if (print == 1) {
        cout << "DFS: ";
    }

    for (int i = 0; i < size; i++) {
        //ops.count();
        if (graph->allNodes[i]->color == 0) { // if white
            DFSVisit(graph, graph->allNodes[i], time, print, NULL, nrEdges);
        }
    }
}


void topologicalSort(GraphT* graph, int size, int print) {
    stack<int> topoS;
    int time = 0;
    for (int i = 0; i < size; i++) {
        if (graph->allNodes[i]->color == 0) { 
            DFSVisit(graph, graph->allNodes[i], time, print, &topoS, 1);
        }
    }

    cout << "Topological Sort Order: ";
    while (!topoS.empty()) {
        cout << topoS.top() << " ";
        topoS.pop();
    }
    cout << endl;
}


void strongCon(NodeT* v, int& index, stack<NodeT*>& S, int& tarjanId) {
    v->index = index;
    v->lowlink = index;
    index++;
    S.push(v);
    v->onStack = true;

    int i = 0;
    while (v->links[i] != NULL) {
        NodeT* w = v->links[i];
        if (w->index == -1) { 
            strongCon(w, index, S, tarjanId);
            v->lowlink = min(v->lowlink, w->lowlink);
        }
        else if (w->onStack) { 
            v->lowlink = min(v->lowlink, w->index);
        }
        i++;
    }

    if (v->lowlink == v->index) {
        NodeT* w;
        do {
            w = S.top();
            S.pop();
            w->onStack = false;
            w->tarjanId = tarjanId;
        } while (w != v);
        tarjanId++;
    }
}

void findSCCs(GraphT* graph, int size) {
    int index = 0;
    stack<NodeT*> S;
    int tarjanId = 0;

    for (int i = 0; i < size; i++) {
        if (graph->allNodes[i]->index == -1) {
            strongCon(graph->allNodes[i], index, S, tarjanId);
        }
    }

    cout << "Strong conn:" << endl;
    for (int id = 0; id < tarjanId; id++) {
        for (int i = 0; i < size; i++) {
            if (graph->allNodes[i]->tarjanId == id) {
                cout << graph->allNodes[i]->key << " ";
            }
        }
        cout << endl;
    }
}


void printAdjency(GraphT *graph, int size) {
    int i,j;
    NodeT* aux;
    for (i = 0; i < size; i++) {
        cout << "De la: " << graph->allNodes[i]->key << " copii: ";
        aux = graph->allNodes[i];
        j = 0;
        while (aux->links[j] != NULL) {
            cout << aux->links[j]->key << " ";
            j++;
        }
        cout << endl;
    }
    cout << endl;
}


void demo() {
    NodeT* aux;
    int i = 0;

    GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    for (i = 0; i < 1000; i++) {
        graph->allNodes[i] = NULL;
    }

    //graph->allNodes[4] = create(4, graph);

    //cout << graph->allNodes[4]->key;

    for (i = 0; i < 10; i++) {
        graph->allNodes[i] = create(i, graph);
    }

    //cout << graph->allNodes[5]->key;

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 5);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 8);
    addEdge(graph, 2, 9);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 8);
    addEdge(graph, 5, 6);
    addEdge(graph, 5, 7);

    printAdjency(graph, 10);

    DFS(graph, 10, 1, 1);
    cout << endl;

    //printAdjency(graph, 10);

    for (int i = 0; i < 10; i++) {
        NodeT* node = graph->allNodes[i];
        cout << node->key << " first t = " << node->time
            << " finish t = " << node->finishTime << endl;
    }


}


void demoTopological() {
    NodeT* aux;
    int i = 0;

    GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    for (i = 0; i < 1000; i++) {
        graph->allNodes[i] = NULL;
    }

    for (i = 0; i < 10; i++) {
        graph->allNodes[i] = create(i, graph);
    }

    int chooseOrDir = 1;
    if (chooseOrDir == 0) {
        addEdgeDir(graph, 0, 1);
        addEdgeDir(graph, 0, 5);
        addEdgeDir(graph, 0, 3);
        addEdgeDir(graph, 1, 2);
        addEdgeDir(graph, 1, 5);
        addEdgeDir(graph, 2, 8);
        addEdgeDir(graph, 2, 9);
        addEdgeDir(graph, 3, 4);
        addEdgeDir(graph, 4, 8);
        addEdgeDir(graph, 5, 6);
        addEdgeDir(graph, 5, 7);
    }
    else {
        addEdge(graph, 0, 1);
        addEdge(graph, 0, 5);
        addEdge(graph, 0, 3);
        addEdge(graph, 1, 2);
        addEdge(graph, 1, 5);
        addEdge(graph, 2, 8);
        addEdge(graph, 2, 9);
        addEdge(graph, 3, 4);
        addEdge(graph, 4, 8);
        addEdge(graph, 5, 6);
        addEdge(graph, 5, 7);
    }

    

   // printAdjency(graph, 10);

    topologicalSort(graph, 10, 0);
    cout << endl;

    for (int i = 0; i < 10; i++) {
        NodeT* node = graph->allNodes[i];
        cout << node->key << " first t = " << node->time
            << " finish t = " << node->finishTime << endl;
    }
}


void demoTarjan() {
    GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    for (int i = 0; i < 1000; i++) {
        graph->allNodes[i] = NULL;
    }

    for (int i = 0; i < 10; i++) {
        graph->allNodes[i] = create(i, graph);
    }

    addEdgeDir(graph, 0, 1);
    addEdgeDir(graph, 1, 2);
    addEdgeDir(graph, 2, 0);
    addEdgeDir(graph, 1, 3);
    addEdgeDir(graph, 3, 4);
    addEdgeDir(graph, 4, 6);
    addEdgeDir(graph, 5, 3);
    addEdgeDir(graph, 6, 5);
    addEdgeDir(graph, 6, 7);
    addEdgeDir(graph, 7, 8);
    addEdgeDir(graph, 8, 6);

    int j = 0;
    for (int i = 0; i < 10; i++) {
        cout << graph->allNodes[i]->key << " : ";
        j = 0;
        while (graph->allNodes[i]->links[j] != NULL) {
            cout << graph->allNodes[i]->links[j]->key << " ";
            j++;
        }
        cout << endl;
    }

    findSCCs(graph, 10);
}


void perf() {
   // GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    int n, j = 0;
    int a[10000], b[10000];

    for (n = 1000; n < 2500; n = n + 100) {
        GraphT* graph = (GraphT*)malloc(sizeof(GraphT));

        for (int i = 0; i < 102; i++) {
              graph->allNodes[i] = create(i,graph);
        }

        //FillRandomArray(a, n * 2, 0, 99, false, 0);   // for 100 nodes
        for (j = 0; j < (n*2) - 1; j = j + 2) {
            addEdge(graph, a[j], a[j + 1]);
        }

        DFS(graph, 100, 0, n);

        free(graph);

    }

    //p.reset("next");

    for (n = 100; n < 200; n = n + 10) {
        GraphT* graph = (GraphT*)malloc(sizeof(GraphT));

        for (int i = 0; i < n + 2; i++) {
            graph->allNodes[i] = create(i, graph);
        }

        //FillRandomArray(a, 2000 * 2, 0, n, false, 0);   // for 100 nodes
        for (j = 0; j < 4000 - 1; j = j + 2) {
            addEdge(graph, a[j], a[j + 1]);
        }

        DFS(graph, n, 0, n);

        free(graph);

    }


    /*
    for (int i = 0; i < 10; i++) {
        graph->allNodes[i] = create(i, graph);
    }
    */

    //p.showReport();
}


int main()
{
    demo();

    cout << endl;

    demoTopological();

    cout << endl;

    demoTarjan();

    perf();

    return 0;
}
