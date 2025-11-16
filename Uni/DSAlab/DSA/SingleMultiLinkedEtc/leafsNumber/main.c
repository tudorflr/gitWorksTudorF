#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *left,*right;
}NodeT;

NodeT *create(int key,int *cnt){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode){
        printf("obo");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->key=key;
    *cnt=1;
    return newnode;
}

NodeT *create2(int key,int *cnt){
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    if(!newnode){
        printf("obo");
        exit(-1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->key=key;
    *cnt=1;
    return newnode;
}

NodeT *insert(int key,NodeT *root,int *cnt,int *cntm){
    if(root==NULL){
        return create(key,cnt);
    }else{
        if(key<root->key){
            (*cnt)++;
            if(*cnt>*cntm){
                *cntm=*cnt;
            }
            root->left=insert(key,root->left,cnt,cntm);
        } else if(key>root->key){
            (*cnt)++;
            if(*cnt>*cntm){
                *cntm=*cnt;
            }
            root->right=insert(key,root->right,cnt,cntm);
        }
    }
}

NodeT *insert2(int key,NodeT *root2,int *cnt,int *cntm){
    if(root2==NULL){
        return create(key,cnt);
    }else{
        if(key<root2->key){
            (*cnt)++;
            if(*cnt>*cntm){
                *cntm=*cnt;
            }
            root2->left=insert2(key,root2->left,cnt,cntm);
        } else if(key>root2->key){
            (*cnt)++;
            if(*cnt>*cntm){
                *cntm=*cnt;
            }
            root2->right=insert2(key,root2->right,cnt,cntm);
        }
    }
}

NodeT *frunze(NodeT *root,int *cntf){
    if(root==NULL){
       return;
    }
    if(root->left!=NULL && root->right!=NULL){
        frunze(root->left, cntf);
        frunze(root->right, cntf);
    }else if(root->left==NULL && root->right!=NULL){
        frunze(root->right, cntf);
    }else if(root->left!=NULL && root->right==NULL){
        frunze(root->left, cntf);
    }else{
        (*cntf)++;
    }
}

NodeT *compar(NodeT *root,int *cntf,NodeT *root2){
    if(root==NULL){
       return;
    }
    if(root->left!=NULL && root->right!=NULL){
            if(root->key==root2->key){
            printf("yes");
        } else {
            printf("no");
        }
        compar(root->left, cntf,root2->left);
        compar(root->right, cntf,root2->left);
        //compar(root2->left, cntf);
        //compar(root2->right, cntf);
    }else if(root->left==NULL && root->right!=NULL){
        if(root->key==root2->key){
            printf("yes");
        } else {
            printf("no");
        }
        compar(root->right, cntf, root2->right);
        //compar(root2->right, cntf);
    }else if(root->left!=NULL && root->right==NULL){
        if(root->key==root2->key){
            printf("yes");
        } else {
            printf("no");
        }
        compar(root->left, cntf, root2->left);
        //compar(root2->left, cntf);
    } else{
        printf("yes");  // nu e chiar perfect outputul dar se poate rezolva
    }
}

int main()
{
    int cnt=1,cntm=1,cntf=0;
    NodeT *root=NULL;
    NodeT *root2=NULL;
    root=insert(30,root,&cnt,&cntm);
    insert(20,root,&cnt,&cntm);
    insert(25,root,&cnt,&cntm);
    insert(40,root,&cnt,&cntm);

    root2=insert(30,root2,&cnt,&cntm);
    insert(20,root2,&cnt,&cntm);
    insert(25,root2,&cnt,&cntm);
    insert(40,root2,&cnt,&cntm);


   // insert(15,root,&cnt,&cntm);
   // insert(10,root,&cnt,&cntm);
   // insert(5,root,&cnt,&cntm);

    printf("%d ", root->key);
    printf("%d ", root->right->key);
    printf("%d ", root->left->key);
    printf("%d ", root->left->right->key);
    printf("\n");
    printf("%d ", root2->key);
    printf("%d ", root2->right->key);

    compar(root, &cntf, root2);

   //printf("\nInaltime:%d", cntm);
   // frunze(root, &cntf);
   // printf("\nFrunze:%d", cntf);
    return 0;
}
