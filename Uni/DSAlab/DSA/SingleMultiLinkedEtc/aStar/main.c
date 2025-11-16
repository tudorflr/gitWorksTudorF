#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct _vertexlistNodeT {
    struct vertex *v;
    struct _vertexlistNodeT *next;
    int weight;
} vertexlistNodeT;   // nu merge bine dar am incercat

typedef struct _vertexlist {
    vertexlistNodeT *first;
} vertexlist;

typedef struct vertex {
    int id;
    int distance;
    int visited;
    struct vertex *parent;
    vertexlist *neigh;
} VertexT;

vertexlistNodeT *create(VertexT *v, int weight) {
    vertexlistNodeT *node = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (node) {
        node->v = v;
        node->weight = weight;
        node->next = NULL;
    }
    return node;
}

void insert_vertex(vertexlist *list, VertexT *v) {
    v->neigh = (vertexlist *)malloc(sizeof(vertexlist));
    if (v->neigh == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    v->neigh->first = NULL;

    vertexlistNodeT *new_node = create(v, 0);
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    new_node->next = list->first;
    list->first = new_node;
}

void insert_edge(VertexT *start, VertexT *end, int wei) {
    if (start->neigh == NULL) {
        start->neigh = (vertexlist *)malloc(sizeof(vertexlist));
        if (start->neigh == NULL) {
            printf("Memory allocation failed\n");
            exit(-1);
        }
        start->neigh->first = NULL;
    }
    vertexlistNodeT *new_edge = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (new_edge == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    new_edge->v = end;
    new_edge->weight = wei;
    new_edge->next = NULL;
    vertexlistNodeT *current = start->neigh->first;
    if (current == NULL) {
        start->neigh->first = new_edge;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_edge;
    }
}

int heuristic(VertexT *start, VertexT *goal) {
    return abs(goal->id - start->id);
}

void a_star(vertexlistNodeT *current, int tovisit[50], int tovisitweight[50], int heuristicCost[50], VertexT *parents[50], int *cnt1, int weightuntilthen, VertexT *goal) {
    if (current->v->neigh->first != NULL) {
        vertexlistNodeT *currentneigh = current->v->neigh->first;
        while (currentneigh != NULL) {
            if (currentneigh->v->visited == 0) {
                tovisit[(*cnt1)] = currentneigh->v->id;
                tovisitweight[(*cnt1)] = currentneigh->weight + weightuntilthen;
                heuristicCost[(*cnt1)] = tovisitweight[(*cnt1)] + heuristic(currentneigh->v, goal);
                parents[(*cnt1)] = current->v;
                (*cnt1) = (*cnt1) + 1;
            }
            currentneigh = currentneigh->next;
        }
    }
}

void print_path(VertexT *goal) {
    if (goal == NULL) {
        return;
    }
    print_path(goal->parent);
    printf("%d ", goal->id);
}

int main() {
    int tovisit[50] = {0};
    int tovisitweight[50] = {0};
    int heuristicCost[50] = {0};
    VertexT *parents[50] = {NULL};
    int cnt1 = 0, cntforall = 1, cntforallmax = 7, weightuntilthen = 0;
    int i;
    VertexT v1 = {1, 0, 0, NULL, NULL};
    VertexT v2 = {2, 0, 0, NULL, NULL};
    VertexT v3 = {3, 0, 0, NULL, NULL};
    VertexT v4 = {4, 0, 0, NULL, NULL};
    VertexT v5 = {5, 0, 0, NULL, NULL};
    VertexT v6 = {6, 0, 0, NULL, NULL};
    VertexT v7 = {7, 0, 0, NULL, NULL};

    vertexlist list;
    list.first = NULL;

    insert_vertex(&list, &v1);
    insert_vertex(&list, &v2);
    insert_vertex(&list, &v3);
    insert_vertex(&list, &v4);
    insert_vertex(&list, &v5);
    insert_vertex(&list, &v6);
    insert_vertex(&list, &v7);

    insert_edge(&v1, &v2, 22);
    insert_edge(&v1, &v3, 11);
    insert_edge(&v1, &v5, 5);
    insert_edge(&v1, &v7, 5);
    insert_edge(&v2, &v3, 55);
    insert_edge(&v2, &v4, 41);
    insert_edge(&v2, &v7, 33);
    insert_edge(&v3, &v4, 8);
    insert_edge(&v3, &v5, 4);
    insert_edge(&v3, &v6, 9);
    insert_edge(&v4, &v6, 17);
    insert_edge(&v4, &v7, 9);
    insert_edge(&v5, &v7, 20);
    insert_edge(&v6, &v7, 80);
    insert_edge(&v7, &v1, 90);

    int rootbfs = 0;
    printf("Choose node to start from: ");
    // scanf("%d", &rootbfs);
    rootbfs = 1;
    printf("%d\n", rootbfs);
    vertexlistNodeT *current = list.first;
    while (current != NULL) {
        if (current->v->id == rootbfs) {
            break;
        }
        current = current->next;
    }

    VertexT *goal = &v4;

    current->v->visited = 1;
    a_star(current, tovisit, tovisitweight, heuristicCost, parents, &cnt1, weightuntilthen, goal);

    int maxforchoose = 100, nextnode = 0, nextHeuristic = 100;
    while (cntforall < cntforallmax) {
        maxforchoose = 100;
        nextHeuristic = 100;
        for (i = 0; i < cnt1; i++) {
            if (tovisit[i] != 0 && heuristicCost[i] < nextHeuristic) {
                nextHeuristic = heuristicCost[i];
                maxforchoose = tovisitweight[i];
                nextnode = tovisit[i];
            }
        }
        weightuntilthen = maxforchoose;
        printf(" %d->%d ", nextnode, maxforchoose);
        for (i = 0; i < cnt1; i++) {
            if (tovisit[i] == nextnode) {
                tovisit[i] = 0;
            }
        }
        current = list.first;
        while (current != NULL) {
            if (current->v->id == nextnode) {
                break;
            }
            current = current->next;
        }
        current->v->visited = 1;
        current->v->parent = parents[i];
        cntforall++;
        if (current->v->id == goal->id) {
            break;
        }
        a_star(current, tovisit, tovisitweight, heuristicCost, parents, &cnt1, weightuntilthen, goal);
    }

    printf("\nPath from start to goal: ");
    print_path(goal);
    printf("\n");

    return 0;
}
