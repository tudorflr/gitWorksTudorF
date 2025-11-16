#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int truck_id;
    struct node *next;
} NodeT;

typedef struct
{
    int nrElem;
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createEmptyList()
{
    ListT *listPtr= (ListT *)malloc(sizeof(ListT));
    listPtr->nrElem=0;
    listPtr->first=NULL;
    return listPtr;
}

NodeT *createNode(int id)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    p->truck_id=id;
    p->next=NULL;
    return p;
}
int isEmpty( ListT *mylist)
{
    return mylist->first==NULL;
}

void insertAtFront( ListT *road, NodeT *p)
{
    p->next=road->first;
    if( isEmpty(road)==1) road->last=p;
    road->first=p;
    road->nrElem++;
}

void printList( ListT *mylist)
{
    NodeT *p=mylist->first;
    while( p != NULL)
    {
        printf( "%d ", p->truck_id);
        p=p->next;
    }
}
int listContainsElem( ListT *mylist, int key)
{
    NodeT *p=mylist->first;
    while(p)
    {
        if(p->truck_id==key) return 1;
        p=p->next;
    }
    return 0;
}
void deleteFirst( ListT *mylist)
{
    NodeT *n=mylist->first->next;
    free(mylist->first);
    mylist->first=n;
}
void insertFirst( ListT *mylist, int key)
{
    NodeT *n=(NodeT *)malloc( sizeof(NodeT));
    n->truck_id=key;
    n->next=mylist->first;
    mylist->first=n;
}
void deleteElem( ListT *mylist, int key)
{
    if( mylist->first->truck_id==key)
    {
        deleteFirst(mylist);
        return;
    }
    NodeT *current=mylist->first;
    NodeT *aux=NULL;
    while( current)
    {
        if( current->truck_id==key)
        {
            aux->next=current->next;
            free(current);
            return;
        }
        aux=current;
        current=current->next;
    }
}
void *deleteLast( ListT *listPtr)
{
    NodeT *q, *q1;
    q1=NULL;
    q=listPtr->first;
    if( q != 0)
    {
        while( q != listPtr->last)
        {
            q1=q;
            q=q->next;
        }
        if( q==listPtr->first)
        {
            listPtr->first = listPtr->last = NULL;
        }
        else
        {
            q1->next=NULL;
            listPtr->last=q1;
        }

    }

}

void enterGarage(ListT *road, ListT*garage, int id)
{
    if(  listContainsElem(road, id))
    {
        deleteElem(road, id);
        insertFirst(garage, id);
    }
    else printf("\nTruck %d not on road", id);

}
int exitGarage(ListT *garage, int key)
{
    if( garage->last->truck_id==key)
    {
        deleteLast(garage);
        return 1;
    }
    return 0;
}
int main()
{
    ListT *road = createEmptyList();
    ListT *garage = createEmptyList();

    // Insert some trucks onto the road
    insertAtFront(road, createNode(101));
    insertAtFront(road, createNode(102));
    insertAtFront(road, createNode(103));
    insertAtFront(road, createNode(104));

    printf("Trucks on the road: ");
    printList(road);
    printf("\n");

    // Move a truck from the road to the garage
    enterGarage(road, garage, 103);

    printf("Trucks on the road after moving 103 to the garage: ");
    printList(road);
    printf("\n");

    enterGarage(road, garage, 101);

    printf("Trucks on the road after moving 101 to the garage: ");
    printList(road);
    printf("\n");

    printf("Trucks in the garage: ");
    printList(garage);
    printf("\n");

    // Remove a truck from the garage
    exitGarage(garage, 103);

    printf("Trucks in the garage after removing 103: ");
    printList(garage);
    printf("\n");

    // Clean up memory
    while (!isEmpty(road)) {
        deleteFirst(road);
    }
    free(road);

    while (!isEmpty(garage)) {
        deleteFirst(garage);
    }
    free(garage);
    return 0;
}
