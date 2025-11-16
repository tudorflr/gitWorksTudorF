#include "bfs.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

#include <queue>
#include <stack>

using namespace std;


int get_neighbors(const Grid* grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    int i, j, x, y, returnCnt = 0, visitedArr[4] = { 0,0,0,0 };

    /*
    if (grid->mat[p.col][p.row] != 0) {   //  not sure daca trebuia si daca ii corect
        return 0;
    }
    */

    neighb[0].col = p.col;
    neighb[0].row = p.row - 1; // up

    neighb[1].col = p.col + 1; // right
    neighb[1].row = p.row;

    neighb[2].col = p.col;
    neighb[2].row = p.row + 1; // down

    neighb[3].col = p.col - 1; // left
    neighb[3].row = p.row;


    i = 0;
    j = 3;
    while (i <= j) {
        int x = neighb[i].row;
        int y = neighb[i].col;

        if (x < 0 || x >= grid->rows || y < 0 || y >= grid->cols || grid->mat[x][y] != 0) {
            if (i < j) {
                swap(neighb[i], neighb[j]);
                j--;
            }
            else {
                i++;
            }
        }
        else {
            returnCnt++;
            i++;
        }
    }

    return returnCnt;

}

void grid_to_graph(const Grid* grid, Graph* graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node* nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (grid->mat[i][j] == 0) {
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }
            else {
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (nodes[i][j] != NULL) {
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for (i = 0; i < graph->nrNodes; ++i) {
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if (graph->v[i]->adjSize != 0) {
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for (j = 0; j < graph->v[i]->adjSize; ++j) {
                if (neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0) {
                    graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if (k < graph->v[i]->adjSize) {
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph* graph)
{
    if (graph->v != NULL) {
        for (int i = 0; i < graph->nrNodes; ++i) {
            if (graph->v[i] != NULL) {
                if (graph->v[i]->adj != NULL) {
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph* graph, Node* s, Operation* op)
{
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->parent = nullptr;
        if (op != NULL) op->count(3);
    }
    s->color = COLOR_GRAY;
    s->dist = 0;
    s->parent = nullptr;
    if (op != NULL) op->count(3);

    queue<Node*> q;
    q.push(s);

    while (!q.empty())
    {
        Node* u = q.front();
        q.pop();

        for (int i = 0; i < u->adjSize; i++)
        {
            Node* v = u->adj[i];
            if (op != NULL) op->count();
            if (v->color == COLOR_WHITE)
            {
                v->color = COLOR_GRAY;
                v->dist = u->dist + 1;
                v->parent = u;
                if (op != NULL) op->count(3);
                q.push(v);
            }
        }
        u->color = COLOR_BLACK;
        if (op != NULL) op->count();
    }
}

void print_bfs_tree(Graph* graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int* p = NULL; //the parent array
    Point* repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int* transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for (int i = 0; i < graph->nrNodes; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            transf[i] = n;
            ++n;
        }
        else {
            transf[i] = -1;
        }
    }
    if (n == 0) {
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for (int i = 0; i < graph->nrNodes && !err; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            if (transf[i] < 0 || transf[i] >= n) {
                err = 1;
            }
            else {
                repr[transf[i]] = graph->v[i]->position;
                if (graph->v[i]->parent == NULL) {
                    p[transf[i]] = -1;
                }
                else {
                    err = 1;
                    for (int j = 0; j < graph->nrNodes; ++j) {
                        if (graph->v[i]->parent == graph->v[j]) {
                            if (transf[j] >= 0 && transf[j] < n) {
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if (!err) {
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs

        int i = 0, j = 0, aux, auxPos; // trb sa rezolv n

        while (p[i] != -1) {
            i++;
        }

        stack<int> stackPretty;
        stack<int> stackSpaces;

        stackPretty.push(i);
        stackSpaces.push(1);

        cout << endl << "pretty print :";

        while (stackPretty.empty() == false) {
            aux = stackPretty.top();
            auxPos = stackSpaces.top();
            stackPretty.pop();
            stackSpaces.pop();

            cout << endl;
            for (j = 0; j < auxPos; j++) {
                cout << "     ";
            }
            cout << "(" << repr[aux].row << ", " << repr[aux].col << ")";

            for (i = 0; i < n; i++) {
                if (p[i] == aux) {
                    stackPretty.push(i);
                    stackSpaces.push(auxPos + 1);
                }
            }
        }

        cout << endl;
    }

    if (p != NULL) {
        free(p);
        p = NULL;
    }
    if (repr != NULL) {
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph* graph, Node* start, Node* end, Node* path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
    return -1;
}



void makeGraph(Graph* graph, int edges, int vertices)
{
    srand(time(NULL));

    for (int i = 0; i < vertices; i++) {
        graph->v[i]->adjSize = 0;
        graph->v[i]->adj = (Node**)malloc(vertices * sizeof(Node*));
    }

    int randomArr[10000], auxArr[10000];
    FillRandomArray(randomArr, vertices, 0, vertices - 1, true, 0);

    for (int i = 0; i < vertices - 1; i++) {
        int u = randomArr[i];
        int v = randomArr[i + 1];

        graph->v[u]->adj[graph->v[u]->adjSize++] = graph->v[v];

        graph->v[v]->adj[graph->v[v]->adjSize++] = graph->v[u];
    }

    int currentEdges = vertices - 1;
    while (currentEdges < edges) {
        int ur = rand() % vertices;
        int vr = rand() % vertices;

        int u = randomArr[ur];
        int v = randomArr[vr];

        if (u != v) {
            int merge = 0;
            for (int i = 0; i < graph->v[u]->adjSize; i++) {
                if (graph->v[u]->adj[i] == graph->v[v]) {
                    merge = 1;
                    break;
                }
            }
            if (merge == 0) {
                graph->v[u]->adj[graph->v[u]->adjSize++] = graph->v[v];

                graph->v[v]->adj[graph->v[v]->adjSize++] = graph->v[u];

                currentEdges++;
            }
        }
    }
}



void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for (n = 1000; n <= 4500; n += 100) {
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        makeGraph(&graph, n, graph.nrNodes);

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for (n = 100; n <= 200; n += 10) {
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected

        makeGraph(&graph, 4500, graph.nrNodes);

        //
        
        /*
        srand(time(NULL));
        int arr[10000] = { 0 };
        for (int k = 0; k < n; k++) {
            graph.v[k]->adjSize = 0;
            // Allocate memory for adjacency list of each node
            graph.v[k]->adj = (Node**)malloc(n * sizeof(Node*));
        }
        */
        //

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
