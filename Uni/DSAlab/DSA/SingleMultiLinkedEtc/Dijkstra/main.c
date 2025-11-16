#include <stdlib.h>

typedef struct _vertexlistNodeT {
    struct vertex *v;
    struct _vertexlistNodeT *next;
    int weight;
} vertexlistNodeT;

typedef struct _vertexlist {
    vertexlistNodeT *first;
} vertexlist;

typedef struct vertex {
    int id;
    int distance;
    int visited;
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
            printf("nu");
            exit(-1);
        }
        start->neigh->first = NULL;
    }
    vertexlistNodeT *new_edge = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (new_edge == NULL) {
        printf("nu");
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

void dijkstra(vertexlistNodeT *current, int tovisit[50], int tovisitweight[50], int *cnt1, int weightuntilthen){
    if(current->v->neigh->first != NULL){
        vertexlistNodeT *currentneigh = current->v->neigh->first;
    while(currentneigh!=NULL){
        if(currentneigh->v->visited == 0){
            tovisit[(*cnt1)]=currentneigh->v->id;
            tovisitweight[(*cnt1)]=currentneigh->weight+weightuntilthen;
            (*cnt1)=(*cnt1)+1;
        }
        currentneigh=currentneigh->next;
    }
    }
}

int main() {
    int tovisit[50] = {0};
    int tovisitweight[50] = {0};
    int cnt1 = 0, cntforall = 1, cntforallmax = 7, weightuntilthen=0;
    int i;
    VertexT v1 = {1, 0, 0, NULL};
    VertexT v2 = {2, 0, 0, NULL};
    VertexT v3 = {3, 0, 0, NULL};
    VertexT v4 = {4, 0, 0, NULL};
    VertexT v5 = {5, 0, 0, NULL};
    VertexT v6 = {6, 0, 0, NULL};
    VertexT v7 = {7, 0, 0, NULL};

    vertexlist list;
    list.first = NULL;

    insert_vertex(&list, &v1);
    insert_vertex(&list, &v2);
    insert_vertex(&list, &v3);
    insert_vertex(&list, &v4);
    insert_vertex(&list, &v5);
    insert_vertex(&list, &v6);
    insert_vertex(&list, &v7);

/*
    insert_edge(&v7, &v5, 10);
  //  insert_edge(&v1, &v2, 15);
    insert_edge(&v2, &v4, 20);
    insert_edge(&v2, &v6, 25);
    insert_edge(&v4, &v5, 5);
   // insert_edge(&v2, &v1, 3);
    insert_edge(&v1, &v4, 30);
    insert_edge(&v1, &v6, 22);
    insert_edge(&v6, &v7, 21);
    insert_edge(&v6, &v1, 26);
    insert_edge(&v6, &v4, 19);
    insert_edge(&v5, &v2, 19);
*/


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
    rootbfs=1;
    printf("%d", rootbfs);
    vertexlistNodeT *current = list.first;
    while (current != NULL) {
        if (current->v->id == rootbfs) {
            break;
        }
        current = current->next;
    }

    current->v->visited=1;
    dijkstra(current,tovisit,tovisitweight,&cnt1,weightuntilthen);

    int maxforchoose=100,nextnode=0;
    while(cntforall<cntforallmax){
        maxforchoose=100;
        for(i=0;i<cnt1;i++){
          //  printf("%d", tovisit[i]);
            if(tovisit[i]!=0 && tovisitweight[i]<maxforchoose){
                maxforchoose=tovisitweight[i];
                nextnode=tovisit[i];
            }
        }
        weightuntilthen=maxforchoose;
        printf(" %d->%d ", nextnode,maxforchoose);
        for(i=0;i<cnt1;i++){
            if(tovisit[i]==nextnode){
                tovisit[i]=0;
            }
        }
        current=list.first;
        while(current != NULL){
            if(current->v->id==nextnode){
            break;
        }
        current=current->next;
    }
        current->v->visited=1;
        cntforall++;
        dijkstra(current,tovisit,tovisitweight,&cnt1,weightuntilthen);
    }


    printf("\n");

    printf("Vertex %d neighbors:\n", v1.id);
    vertexlistNodeT *current_neigh = v1.neigh->first;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    printf("Vertex %d neighbors:\n", v2.id);

    current_neigh = v2.neigh->first;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    printf("Vertex %d neighbors:\n", v4.id);
    current_neigh = v4.neigh != NULL ? v4.neigh->first : NULL;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    printf("Vertex %d neighbors:\n", v5.id);
    current_neigh = v5.neigh != NULL ? v5.neigh->first : NULL;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    printf("Vertex %d neighbors:\n", v6.id);
    current_neigh = v6.neigh != NULL ? v6.neigh->first : NULL;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    printf("Vertex %d neighbors:\n", v7.id);
    current_neigh = v7.neigh != NULL ? v7.neigh->first : NULL;
    while (current_neigh != NULL) {
        printf("  Neighbor id: %d\n", current_neigh->v->id);
        current_neigh = current_neigh->next;
    }

    return 0;
}
