#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vertexlistNodeT {
    struct vertex *v;
    struct _vertexlistNodeT *next;
  //  int weight;
} vertexlistNodeT;

typedef struct _vertexlist {
    vertexlistNodeT *first;
} vertexlist;

typedef struct vertex {
    int id;
  //  int distance;
  //  int parentid;
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
        fprintf(stderr, "nu");
        exit(-1);
    }
    new_node->next = list->first;
    list->first = new_node;
}

void insert_edge(VertexT *start, VertexT *end) {
    if (start->neigh == NULL) {
        start->neigh = (vertexlist *)malloc(sizeof(vertexlist));
        if (start->neigh == NULL) {
            fprintf(stderr, "nu");
            exit(-1);
        }
        start->neigh->first = NULL;
    }
    vertexlistNodeT *new_edge = (vertexlistNodeT *)malloc(sizeof(vertexlistNodeT));
    if (new_edge == NULL) {
        fprintf(stderr, "nu");
        exit(-1);
    }
    new_edge->v = end;
  //  new_edge->weight = 0;
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

void bfs(vertexlistNodeT *current, int tovisit[10], int *cnt1, int *cnt2){
    vertexlistNodeT *currentneigh=current->v->neigh->first;
    if(current->v->visited == 0){
    printf("%d \n", current->v->id);
    current->v->visited = 1;
    }
    while(currentneigh != NULL){
        if(currentneigh->v->visited==0){
        printf("%d ", currentneigh->v->id);
        *cnt1=(*cnt1)+1;
        tovisit[*cnt1]=currentneigh->v->id;
        currentneigh->v->visited = 1;
        }
        //printf("  cnt1:%d  ", *cnt1);
        if(currentneigh->next != NULL){
            currentneigh=currentneigh->next;
        } else {
            printf("\n");
            break;
        }
    }
}

int main() {
    int a[10],i=-1,j=0,cnt=0,k=0,l=0,cnt1=-1,cnt2=0;
    int tovisit[10];
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

    insert_edge(&v7,&v1);
    insert_edge(&v1, &v2);
    insert_edge(&v2, &v4);
    insert_edge(&v4, &v1);
   // insert_edge(&v4, &v2);
    insert_edge(&v4, &v5);
 //   insert_edge(&v2, &v5);
    insert_edge(&v2, &v6);
    insert_edge(&v2, &v1);
    insert_edge(&v1, &v4);
    insert_edge(&v5, &v1);



    vertexlistNodeT *current = list.first;
    while (current != NULL) {
        printf("Vertex id: %d\n", current->v->id);
        current = current->next;
    }

    printf("Choose node to start form:");

    int rootbfs=0;
    scanf("%d", &rootbfs);
    current=list.first;
    while(current != NULL){
            if(current->v->id==rootbfs){
            break;
        }
        current=current->next;
    }
    //printf("\n%d", current->v->id);

    bfs(current, tovisit, &cnt1, &cnt2);

    while(cnt2<=cnt1){
        current=list.first;
        while(current != NULL){
            if(current->v->id==tovisit[cnt2]){
            bfs(current, tovisit, &cnt1, &cnt2);
            cnt2++;
           // printf("   cnt2:%d   ", cnt2);
            break;
            } else {
                current=current->next;
            }
        }
    }

/*
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

   // printf("\n");
   // printf("%d ", tovisit[0]);
   // printf("%d ", tovisit[1]);
   // printf("%d ", tovisit[2]);
   // printf("%d", cnt1);
   // printf("%d", cnt2);
*/
    return 0;
}
