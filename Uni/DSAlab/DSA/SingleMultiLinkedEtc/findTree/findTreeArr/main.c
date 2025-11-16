#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char *key;
    int price;
    int amount;
    int dom;
    int doe;
    struct node *left,*right;
}NodeT;


NodeT *create(char *key, int price, int amount, int dom, int doe){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode){
        printf("obo");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->key = strdup(key);
    newnode->price=price;
    newnode->amount=amount;
    newnode->dom=dom;
    newnode->doe=doe;
    return newnode;
}

NodeT *insert(NodeT *root, char *key, int price, int amount, int dom, int doe){
    int cmp;
    if(root==NULL){
        return create(key, price, amount, dom, doe);
    } else {
        cmp = strcmp(key, root->key);
        if(cmp > 0){
            root->right = insert(root->right, key, price, amount, dom, doe);
        } else {
            root->left = insert(root->left, key, price, amount, dom, doe);
        }
    }
    return root;
}

NodeT *maxi(NodeT *root){
    root=root->left;
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

NodeT *deletenode(NodeT *root, char *key){
    if(root == NULL){
        return root;
    }
    int cmp = strcmp(key, root->key);
    if(cmp > 0){
        root->right = deletenode(root->right, key);
    } else if(cmp < 0){
        root->left = deletenode(root->left, key);
    } else{
        if(root->right==NULL && root->left==NULL){
            free(root);
            return NULL;
        } else if(root->right==NULL && root->left!=NULL){
            NodeT *temp=root->left;
            free(root);
            return temp;
        } else if(root->right!=NULL && root->left==NULL){
            NodeT *temp=root->right;
            free(root);
            return temp;
        } else{
            NodeT *temp=maxi(root);
            temp->left=root->left;
            temp->right=root->right;
            free(root);
            return temp;
        }
    }
    return root;
}

NodeT *findkey(NodeT *root,char *fkey,char *key,int price1, int amount1, int dom1, int doe1){
    if(root->left!=NULL && root->right!=NULL){
        if(strcmp(root->key, fkey)==0){
            printf("    YESSIR");
            printf(" %s\n", fkey);
            strcpy(root->key,key);
            root->price=price1;
            root->amount=amount1;
            root->dom=dom1;
            root->doe=doe1;
        }
        findkey(root->left, fkey, key, price1, amount1, dom1, doe1);
        findkey(root->right, fkey, key, price1, amount1, dom1, doe1);
    }else if(root->left!=NULL && root->right==NULL){
        if(strcmp(root->key, fkey)==0){
            printf("YESSIR");
            printf(" %s\n", fkey);
            strcpy(root->key,key);
            root->price=price1;
            root->amount=amount1;
            root->dom=dom1;
            root->doe=doe1;
        }
        findkey(root->left, fkey, key, price1, amount1, dom1, doe1);
    }else if(root->left==NULL && root->right!=NULL){
        if(strcmp(root->key, fkey)==0){
            printf("YESSIR");
            printf(" %s\n", fkey);
            strcpy(root->key,key);
            root->price=price1;
            root->amount=amount1;
            root->dom=dom1;
            root->doe=doe1;
        }
        findkey(root->right, fkey, key, price1, amount1, dom1, doe1);
    }else if(strcmp(root->key, fkey)==0){
        printf("YESIR");
        printf(" %s\n", fkey);
        strcpy(root->key,key);
            root->price=price1;
            root->amount=amount1;
            root->dom=dom1;
            root->doe=doe1;
    }
}

//sectiune 2

typedef struct node2{
    char *key;
    int price;
    int amount;
    int dom;
    int doe;
    struct node2 *left,*right;
}NodeT2;


NodeT2 *create2(char *key, int price, int amount, int dom, int doe){
    NodeT2 *newnode=(NodeT2*)malloc(sizeof(NodeT2));
    if(!newnode){
        printf("obo");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->key = strdup(key);
    newnode->price=price;
    newnode->amount=amount;
    newnode->dom=dom;
    newnode->doe=doe;
    return newnode;
}

NodeT2 *insert2(NodeT2 *root2, char *key, int price, int amount, int dom, int doe){
    int cmp;
    if(root2==NULL){
        return create2(key, price, amount, dom, doe);
    } else {
        cmp = strcmp(key, root2->key);
        if(cmp > 0){
            root2->right = insert2(root2->right, key, price, amount, dom, doe);
        } else {
            root2->left = insert2(root2->left, key, price, amount, dom, doe);
        }
    }
    return root2;
}

NodeT *expired(NodeT *root, char *fkey, NodeT2 *root2){
    if(root->left!=NULL && root->right!=NULL){
        if(strcmp(root->key, fkey)==0){
            root2=insert2(root2, fkey, root->price, root->amount, root->dom, root->doe);
        }
        expired(root->left, fkey, root2);
        expired(root->right, fkey, root2);
    }else if(root->left!=NULL && root->right==NULL){
        if(strcmp(root->key, fkey)==0){
            root2=insert2(root2, fkey, root->price, root->amount, root->dom, root->doe);
        }     // Asta nu merge inca
        expired(root->left, fkey, root2);
    }else if(root->left==NULL && root->right!=NULL){
        if(strcmp(root->key, fkey)==0){
            root2=insert2(root2, fkey, root->price, root->amount, root->dom, root->doe);
        }
        expired(root->right, fkey, root2);
    }else if(strcmp(root->key, fkey)==0){
        root2=insert2(root2, fkey, root->price, root->amount, root->dom, root->doe);
    }
}

/*
NodeT *expired(NodeT *root, int *contor, NodeT2 *root2){
    if(root->left!=NULL && root->right!=NULL){
        if(root->doe % 100 < 23){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3 && (root->doe/10000) < 27){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        }
        expired(root->left, contor, root2);
        expired(root->right, contor, root2);
    }else if(root->left!=NULL && root->right==NULL){
        if(root->doe % 100 < 23){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3 && (root->doe/10000) < 27){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        }
        expired(root->left, contor, root2);
    }else if(root->left==NULL && root->right!=NULL){
        if(root->doe % 100 < 23){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        } else if(root->doe % 100 ==23 && (root->doe / 100)%100 < 3 && (root->doe/10000) < 27){
            if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
        }
        expired(root->right, contor, root2);
    }else if(root->key==contor){
        if(contor==0){
                contor++;
                root2=insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }else{
                insert2(root2, contor, root->price, root->amount, root->dom, root->doe);
            }
    }
}
*/
int main()
{
    int contor=0;
    NodeT *root=NULL;
    NodeT2 *root2=NULL;
    root=insert(root,"D",10,6,120222,120822);
    insert(root,"A",4,12,123451,120820);
    insert(root,"B",0,0,0,0);

    printf(" %s\n", root->key);
    printf(" %s\n", root->left->key);
    printf(" %s\n", root->left->right->key);
   // printf("%d %d %d %d ",root->left->right->price, root->left->right->amount, root->left->right->dom, root->left->right->doe);
   // printf(" %s\n", root->right->key);
   // deletenode(root,"B");

    printf("%d %d %d %d ",root->price, root->amount, root->dom, root->doe);
    findkey(root, "B","BA",12,12,120222,120323);
    printf(" %s\n", root->left->right->key);
    printf("%d %d %d %d ",root->left->right->price, root->left->right->amount, root->left->right->dom, root->left->right->doe);

    expired(root,"A", root2);  // asta nu merge inca

   // root2=insert2(root2,"H",0,0,0,0);
    printf("\n %s\n", root2->key);

    return 0;
}
