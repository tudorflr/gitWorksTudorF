#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char name[10];
    struct node *next;
}NodeT;


void display(NodeT *head)
{
    NodeT *p=head;
    if( head == NULL)
    {
        printf("Empty");
        return;
    }
    do
    {
        printf("%s\n", p->name);
        p=p->next;
    } while(p!=head);
}

NodeT *readNames( FILE *f, int n)
{
    char **v;
    v=(char**)malloc(n*sizeof(char*));
    for( int i=0; i<n; i++)
    {
        v[i]=(char*)malloc(10*sizeof(char));
    }
    NodeT *head=NULL, *tail=NULL;
    for( int i=0; i<n; i++)
    {
        NodeT *p=(NodeT*)malloc(sizeof(NodeT));
        fscanf(f, "%s", *(v+i));
        strcpy( p->name, v[i]);
        p->next=NULL;
        if(head==NULL) head=tail=p;
        else
        {
            tail->next=p;
            tail=p;
        }
        tail->next=head;
    }
    return head;
}

NodeT *playGame( NodeT *head, int n)
{
    while( head->next !=head)
    {
        for( int j=1; j<n-1; j++)
            head=head->next;
            printf("Player who left: %s\n", head->next->name);
            NodeT *p=head->next;
            head->next=p->next;
            free(p);
            head=head->next;

    }
    return head;
}
int main()
{
    FILE *f=fopen("input.txt", "r");
    int n;
    fscanf(f, "%d", &n);

    NodeT *head=readNames(f, n);

    display(head);

    NodeT *winner=playGame(head, n);
    printf("\nWinner is: %s", winner->name);
    return 0;
}

