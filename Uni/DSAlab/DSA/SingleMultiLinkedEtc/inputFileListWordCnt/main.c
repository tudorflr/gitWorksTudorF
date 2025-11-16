#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char word[20];
    struct node *next;
    struct node *prev;
    int count;
}NodeT;

void readText( NodeT **head, char *wordRead)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    p->next=p->prev=NULL;
    strcpy(p->word, wordRead);

    if( *head ==NULL)
    {
        *head=p;
        p->next=p->prev=NULL;

        p->count=1;
        return;
    }

    NodeT *aux=*head;
    while( aux !=NULL)
    {
        if( strcmp( p->word, aux->word) == 0)
        {
            aux->count++;
            free(p);
            return;
        }
        else
        {

            aux=aux->next;
        }
    }
    p->count=1;

    NodeT *currentNode=*head;
    if(strcmp(p->word,(*head)->word)<0){
        *head=p;
        currentNode->prev=*head;
        (*head)->next=currentNode;
        (*head)->prev=NULL;
        return;
    }
    else {
    while( currentNode != NULL)
    {
        if( strcmp(p->word, currentNode->word) < 0)
        {
            insertBefore(p, currentNode);
            return;
        }
        else if(currentNode->next==NULL){
            break;
        }
        else currentNode=currentNode->next;
    }
    }
    currentNode->next=p;
    p->prev=currentNode;
    p->next=NULL;
}
void insertBefore(NodeT *p, NodeT *currentNode)
{
    p->prev=currentNode->prev;
    p->next=currentNode;
    currentNode->prev->next=p;
    currentNode->prev=p;

}
void printList(NodeT *currentNode)
{
    while( currentNode != NULL)
    {
        printf( "%s: ", currentNode->word);
        printf("%d \n", currentNode->count);
        currentNode=currentNode->next;
    }
}

int main()
{
    FILE *f=fopen("data.txt", "r");
    NodeT *head=NULL;
    char word[200];
    while( fscanf(f, "%s", word) != EOF)
    {
        readText(&head, word);
    }
    printList(head);
    fclose(f);
    return 0;
}
