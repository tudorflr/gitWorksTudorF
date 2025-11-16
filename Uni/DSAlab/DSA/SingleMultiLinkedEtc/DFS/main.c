#include <stdio.h>
#include <stdlib.h>

typedef struct _vertexlistNodeT {
    struct vertex *v;
    struct _vertexlistNodeT *next;
} vertexlistNodeT;

typedef struct _vertexlist {
    vertexlistNodeT *first;
} vertexlist;

typedef struct vertex {
    int id;
    int visited;
    vertexlist *neigh;
} VertexT;

vertexlistNodeT *create(VertexT *v) {
    vertexlistNodeT *node = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (node) {
        node->v = v;
        node->next = NULL;
    }
    return node;
}

void insert_vertex(vertexlist *list, VertexT *v) {
    vertexlistNodeT *new_node = create(v);
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    new_node->next = list->first;
    list->first = new_node;
}

void insert_edge(VertexT *start, VertexT *end) {
    if (start->neigh == NULL) {
        start->neigh = (vertexlist *)malloc(sizeof(vertexlist));
        if (start->neigh == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(-1);
        }
        start->neigh->first = NULL;
    }
    vertexlistNodeT *new_edge = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (new_edge == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    new_edge->v = end;
    new_edge->next = start->neigh->first;
    start->neigh->first = new_edge;
}

void dfs(VertexT *v) {
    if (v->visited == 1)
        return;

    printf("%d ", v->id);
    v->visited = 1;

    vertexlistNodeT *currentneigh = v->neigh->first;
    while (currentneigh != NULL) {
        dfs(currentneigh->v);
        currentneigh = currentneigh->next;
    }
}

int main() {
    int tovisit[10];
    int cnt1 = -1;
    int cnt2 = 0;

    VertexT v1 = {1, 0, NULL};
    VertexT v2 = {2, 0, NULL};
    VertexT v4 = {4, 0, NULL};
    VertexT v5 = {5, 0, NULL};
    VertexT v6 = {6, 0, NULL};
    VertexT v7 = {7, 0, NULL};

    vertexlist list;
    list.first = NULL;

    insert_vertex(&list, &v1);
    insert_vertex(&list, &v4);
    insert_vertex(&list, &v2);
    insert_vertex(&list, &v5);
    insert_vertex(&list, &v6);
    insert_vertex(&list, &v7);

    insert_edge(&v7, &v5);
    insert_edge(&v1, &v2);
    insert_edge(&v2, &v4);
    insert_edge(&v4, &v5);
    insert_edge(&v4, &v1);
    insert_edge(&v4, &v2);
    insert_edge(&v2, &v5);
    insert_edge(&v2, &v6);
    insert_edge(&v2, &v1);
    insert_edge(&v1, &v4);
    insert_edge(&v5, &v1);
    insert_edge(&v1, &v7);

    vertexlistNodeT *current = list.first;
    while (current != NULL) {
        printf("Vertex id: %d\n", current->v->id);
        current = current->next;
    }

    printf("Choose node to start from: ");
    int rootbfs = 1;
  //  scanf("%d", &rootbfs);
    current = list.first;
    while (current != NULL) {
        if (current->v->id == rootbfs) {
            break;
        }
        current = current->next;
    }

    dfs(current->v);

    printf("\n");

    return 0;
}
