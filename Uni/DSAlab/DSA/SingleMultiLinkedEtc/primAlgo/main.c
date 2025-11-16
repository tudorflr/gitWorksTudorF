#include <stdio.h>
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
    vertexlistNodeT *new_node = create(v, 0);
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    new_node->next = list->first;
    list->first = new_node;
}

void insert_edge(VertexT *start, VertexT *end, int wei) {
    if (start->neigh == NULL) {
        start->neigh = (vertexlist *)malloc(sizeof(vertexlist));
        if (start->neigh == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(-1);
        }
        start->neigh->first = NULL;
    }
    vertexlistNodeT *new_edge = create(end, wei);
    if (new_edge == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    new_edge->next = start->neigh->first;
    start->neigh->first = new_edge;

    if (end->neigh == NULL) {
        end->neigh = (vertexlist *)malloc(sizeof(vertexlist));
        if (end->neigh == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(-1);
        }
        end->neigh->first = NULL;
    }
    new_edge = create(start, wei);
    if (new_edge == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    new_edge->next = end->neigh->first;
    end->neigh->first = new_edge;
}

void prim(vertexlistNodeT *current, int tovisit[50], int tovisitweight[50], int *cnt1){
    vertexlistNodeT *currentneigh = current->v->neigh->first;
    while(currentneigh!=NULL){
        if(currentneigh->v->visited == 0){
            tovisit[(*cnt1)]=currentneigh->v->id;
            tovisitweight[(*cnt1)]=currentneigh->weight;
            (*cnt1)=(*cnt1)+1;
        }
        currentneigh=currentneigh->next;
    }
}

int main() {
    int tovisit[50] = {0};
    int tovisitweight[50] = {0};
    int cnt1 = 0, cntforall = 1, cntforallmax = 6;
    int i;
    VertexT v1 = {1, 0, 0, NULL};
    VertexT v2 = {2, 0, 0, NULL};
    VertexT v4 = {4, 0, 0, NULL};
    VertexT v5 = {5, 0, 0, NULL};
    VertexT v6 = {6, 0, 0, NULL};
    VertexT v7 = {7, 0, 0, NULL};

    vertexlist list;
    list.first = NULL;

    insert_vertex(&list, &v1);
    insert_vertex(&list, &v4);
    insert_vertex(&list, &v2);
    insert_vertex(&list, &v5);
    insert_vertex(&list, &v6);
    insert_vertex(&list, &v7);

    insert_edge(&v7, &v5, 10);
  //  insert_edge(&v1, &v2, 15);
    insert_edge(&v2, &v4, 20);
    insert_edge(&v2, &v6, 25);
    insert_edge(&v4, &v5, 5);
   // insert_edge(&v2, &v1, 3);
    insert_edge(&v1, &v4, 30);
    insert_edge(&v1, &v6, 22);

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
    prim(current,tovisit,tovisitweight,&cnt1);

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
        printf(" %d", nextnode);
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
        prim(current,tovisit,tovisitweight,&cnt1);
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
