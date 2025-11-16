#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char key;
    struct node *left,*right;
}NodeT;

NodeT *create(char key){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode){
        printf("obo");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->key=key;
    return newnode;
}

NodeT *insert(NodeT *root,char key){
    if(root==NULL){
        return create(key);
    }else{
        if(key>root->key){
            root->right=insert(root->right,key);
        } else{
            root->left=insert(root->left,key);
        }
    }
}

NodeT *maxi(NodeT *root){
    root=root->left;
    while(root->right!=NULL){
        root=root->right;
    }
    return root->key;
}

NodeT *deletenode(NodeT *root,char key){
    NodeT *a;
    if(key>root->key){
        root->right=deletenode(root->right,key);
        return root;
    } else if(key<root->key){
        root->left=deletenode(root->left,key);
        return root;
    } else{
        if(root->right==NULL && root->left==NULL){
            free(root);
            return NULL;
        } else if(root->right==NULL && root->left!=NULL){
            a=root->left;
            free(root);
            return a;
        } else if(root->right!=NULL && root->left==NULL){
            a=root->right;
            free(root);
            return a;
        } else{
            a=maxi(root);
            a->left=root->left;
            a->right=root->right;
            free(root);
            return a;
        }
    }
}

NodeT *findkey(NodeT *root,char fkey){
    if(root->left!=NULL && root->right!=NULL){
        if(root->key == fkey){
            printf("    YESSIR");
        }
        findkey(root->left, fkey);
        findkey(root->right, fkey);
    }else if(root->left!=NULL && root->right==NULL){
        if(root->key == fkey){
            printf("YESSIR");
        }
        findkey(root->left, fkey);
    }else if(root->left==NULL && root->right!=NULL){
        if(root->key == fkey){
            printf("YESSIR");
        }
        findkey(root->right, fkey);
    }else if(root->key==fkey){
        printf("YESIR");
        printf(" %s\n", fkey);
    }
}

int main()
{
    NodeT *root=NULL;
    root=insert(root,'D');
    insert(root,'A');
    insert(root,'B');
    insert(root,'C');

    deletenode(root,'B');



    printf("%c ",root->key);
    printf(" %c ",root->left->key);
    printf(" %c ",root->left->right->key);
   // printf(" %c",root->left->right->right->key);

    findkey(root, 'C');

    return 0;
}
