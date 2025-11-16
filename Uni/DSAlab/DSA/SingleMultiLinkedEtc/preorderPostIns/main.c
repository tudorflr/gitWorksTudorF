#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left,*right,*previous;
}NodeT;

NodeT* create(int key){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode)
    {
        printf("error");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
   // newnode->previous=NULL;
    newnode->key=key;
   // printf("%d ", newnode->key);
    return newnode;
}

/*
NodeT* create(int key){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode)
    {
        printf("error");
        exit(-1);
    }
    newnode->previous->right=NULL;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->previous=NULL;
    newnode->key=key;
   // printf("%d ", newnode->key);
    return newnode;
}
*/

NodeT* insertpreorder(int key,NodeT *root){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(root==NULL){
        return create(key);
    }
    else {
      /*  if(key==0){
            direction=0;
        } else if(key==1){
            direction=1;
        }
        */
        if(root->left==NULL){
            root->left=insertpreorder(key, root->left);
        } else {
            root->right=insertpreorder(key, root->right);
        }
     /*   if(root->left==NULL && direction==0){
            root->left=insertpreorder(key, root->left, direction);
        } else if(direction==0){
            root->right=insertpreorder(key, root->right, direction);
        }
     */
    }
}

NodeT* insertpostorder(int key,NodeT *root){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(root==NULL){
        return create(key);
    }
    else {
        if(root->previous->right==NULL){
            root->previous->right=insertpostorder(key, root->previous->right);
        } else{
            root->previous=insertpostorder(key, root->previous);
        }
    }
}

int main()
{
    int *direction=1;
    NodeT *root=NULL;
    root=insertpreorder(8,root);
    insertpreorder(1,root);
    insertpreorder(2,root);
    insertpreorder(4,root);
    insertpreorder(5,root);

    printf("%d", root->key);
    printf(" %d", root->left->key);
    printf(" %d", root->right->key);
    printf(" %d", root->right->right->key);
    printf(" %d", root->right->left->key);
   // printf(" %d", root->right->key);
    /*
    root=insertpostorder(6,root);
    insertpostorder(5,root);
    insertpostorder(2,root);

    printf("%d", root->key);
    printf(" %d", root->previous->right->key);
    printf(" %d ", root->previous->key);
    */
  /*  while(root=!NULL){
        printf("%d",root->key);
        if(root->right!=NULL){
            root=root->right;
            printf("%d",root->key);
        }
        if(root->left!=NULL){
            root=root->left;
            printf("%d",root->key);
        }
        root=root->right;
    }
    */

    return 0;
}
