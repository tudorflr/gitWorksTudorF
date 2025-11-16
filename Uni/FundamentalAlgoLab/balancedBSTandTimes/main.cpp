/**
* @author Florea Tudor
* @group 30425
*
* lab07 - Dynamic Order Static
*
*   Build uses divide and conquer to always put in the median of 
*   each "subarray" at each step, and sets sizes from bottom to top
*
*   Search operations calculates the ranks of each node, and decides
*   if it needs to search left or right at each step
* 
*   Delete has a lot of ifs for each case, no child, one child, two
*   children and does the job accordingly
* 
*   All 3 operations are linear in time
*
*
*/

#include <iostream>
#include <stdlib.h>
#include <stack>
#include "Profiler.h"
#include <time.h>

Profiler p("lab07");

using namespace std;

typedef struct node {
    int number;
    //int color;  // 0 for red  -  1 for black
    struct node* left;
    struct node* right;
    struct node* parent;
    int height;
    int size;
} NodeT;

NodeT* createBSTnode(int nr) {
    NodeT* newNode = new NodeT();

    newNode->number = nr;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->size = 1;

    return newNode;
}


// BST, then check if all is good, if black is the parent to the inserted node then nothing needs to be done


void prettyPrint(node* root)
{
    int NrOfSp = 0, i;
    stack<node*> stackIter;
    stack<int> nrOfSpaces;
    stackIter.push(root);
    nrOfSpaces.push(0);

    while (stackIter.empty() == false) {
        struct node* aux = stackIter.top();
        //cout << aux->number << " ";
        stackIter.pop();

        NrOfSp = nrOfSpaces.top();
        nrOfSpaces.pop();

        for (i = 0; i < NrOfSp; i++) {
            cout << "    ";
        }
        cout << aux->number;
        cout << endl;

        if (aux->right != NULL) {
            stackIter.push(aux->right);
            nrOfSpaces.push(NrOfSp + 1);
        }
        if (aux->left != NULL) {
            stackIter.push(aux->left);
            nrOfSpaces.push(NrOfSp + 1);
        }
    }
}


void setHeight(NodeT* aux, int heightLevel) {
    if (aux == NULL) {
        return;
    }
    aux->height = heightLevel;

    setHeight(aux->left, heightLevel + 1);
    setHeight(aux->right, heightLevel + 1);
}


NodeT* buildBalancedBST(int first, int last, NodeT* parent, int testSize) {
    Operation opsBuild = p.createOperation("TotalOperations - Build", testSize);
    NodeT* aux = new NodeT();
    int mid;
    if (last - first < 0) {
        return NULL;
    }
    mid = last + first;
    mid = mid / 2;
    aux = createBSTnode(mid);

    opsBuild.count(3);

    if (parent != NULL) {
        aux->parent = parent;
    }

    aux->left = buildBalancedBST(first, mid - 1, aux, testSize);
    aux->right = buildBalancedBST(mid + 1, last, aux, testSize);

    int leftSize = 0, rightSize = 0;
    opsBuild.count(2);
    if (aux->left != NULL) {
        leftSize = aux->left->size;
    }
    if (aux->right != NULL) {
        rightSize = aux->right->size;
    }
    aux->size = 1 + leftSize + rightSize;
    // size ig

    return aux;
}


NodeT* osSelect(NodeT* x, int i, int testSize) {
    Operation opsSelect = p.createOperation("TotalOperations - Select", testSize);
    int r = (x->left ? x->left->size : 0) + 1;
    opsSelect.count();
    if (x->left == NULL) {
        x->size = 0;
    }
    else {
        r = x->left->size;
        r++;
    }

    if (i == r) {
        return x;
    }
    else if (i < r) {
        return osSelect(x->left, i, testSize);
    }
    else {
        return osSelect(x->right, i - r, testSize);
    }
}

/*
void recalibrateSizes(NodeT* root, int keySel, int testSize) {
    Operation opsDelete = p.createOperation("TotalOperations - Delete", testSize);
    if(root==NULL){
        return;
    }
    opsDelete.count(2);
    if (root->size > keySel) {
        root->size = root->size - 1;
    }

    recalibrateSizes(root->left, keySel, testSize);
    recalibrateSizes(root->right, keySel, testSize);
}


void deleteBSTnode(NodeT* root, int keySel, int testSize) {
    Operation opsDelete = p.createOperation("TotalOperations - Delete", testSize);
    cout << endl << "Delete smallest " << keySel << " : " << endl;
    NodeT* aux;
    NodeT* parentAux;
    NodeT* auxTraverse;
    aux = osSelect(root, keySel, testSize); // aici s ar putea sa numere in plus

    auxTraverse = aux;
    opsDelete.count();
    if (auxTraverse->right != NULL) {
        auxTraverse = auxTraverse->right;
    }
    while (auxTraverse->left != NULL) {
        auxTraverse = auxTraverse->left;
        opsDelete.count();
    }

    aux->number = auxTraverse->number;
    aux->size = auxTraverse->size;

    opsDelete.count(2);
    if (auxTraverse->parent != NULL) {
        parentAux = auxTraverse->parent;
        if (parentAux->left != NULL && parentAux->left->number == auxTraverse->number) {  // treaba asta releaga
            parentAux->left = NULL;
        }
        else {
            parentAux->right = NULL;
        }
    }

    delete auxTraverse;

    recalibrateSizes(root, keySel, testSize);

    //prettyPrint(root);
}
*/


void recalibrateSizes(NodeT* node, int testSize) {
    Operation opsDelete = p.createOperation("TotalOperations - Delete", testSize);
    while (node != NULL) {
        opsDelete.count(3);
        int leftSize = (node->left != NULL) ? node->left->size : 0;
        int rightSize = (node->right != NULL) ? node->right->size : 0;
        node->size = 1 + leftSize + rightSize;
        node = node->parent; // Move up to the parent
    }
}

void deleteBSTnode(NodeT*& root, int keySel, int testSize) {
    Operation opsDelete = p.createOperation("TotalOperations - Delete", testSize);
    if (root == NULL) {
        return;
    }
    NodeT* aux = osSelect(root, keySel, testSize);
    if (aux == NULL) {
        return;
    }
    opsDelete.count(2);
    NodeT* parent = aux->parent;

    opsDelete.count();
    if (aux->left == NULL && aux->right == NULL) {   // no child
        if (parent != NULL) {
            opsDelete.count();
            if (parent->left == aux) {
                parent->left = NULL;
            }
            opsDelete.count();
            if (parent->right == aux) {
                parent->right = NULL;
            }
        }
        else {
            root = NULL;
        }
        delete aux;
    }
    else if (aux->left == NULL || aux->right == NULL) {
        NodeT* child = (aux->left) ? aux->left : aux->right;   // one child  // NodeT* child;if (aux->left != nullptr) {child = aux->left;}else {child = aux->right;}
        opsDelete.count();
        if (parent != NULL) {
            opsDelete.count();
            if (parent->left == aux) {
                parent->left = child;
            }
            opsDelete.count();
            if (parent->right == aux) {
                parent->right = child;
            }
        }
        else {
            root = child;
        }
        child->parent = parent;
        delete aux;
    }
    else {
        NodeT* successor = aux->right;
        while (successor->left != NULL) {
            opsDelete.count();
            successor = successor->left;
        }
        opsDelete.count();
        aux->number = successor->number; 
        deleteBSTnode(aux->right, 1, testSize); 
    }

    recalibrateSizes(parent,testSize);  // from parent up changes
}

void demoFirst() {
    int n = 11;
    NodeT* selectNode;
    NodeT* root = buildBalancedBST(1, 11, NULL, 11);
    setHeight(root, 0);

    //cout << root->number;
    //cout << " " << root->left->left->number;

    prettyPrint(root);

    selectNode = osSelect(root, 3, 11);
    cout << "Select: " << selectNode->number << " ";
    selectNode = osSelect(root, 5, 11);
    cout << selectNode->number << endl;

    cout << endl << "Delete smallest " << 4 << " : " << endl;
    deleteBSTnode(root, 4, 11);
    prettyPrint(root);
    cout << endl << "Delete smallest " << 9 << " : " << endl;
    deleteBSTnode(root, 9, 11);
    prettyPrint(root);
    cout << endl << "Delete smallest " << 3 << " : " << endl;
    deleteBSTnode(root, 3, 11);
    prettyPrint(root);

}


void perf() {
    NodeT* root;   // poate trb reinitializare
    int f;
    int n, i, j, randomNr;

    srand(time(NULL));

    for (n = 100; n <= 1000; n += 100) {
        root = NULL;
        root = buildBalancedBST(1, n, NULL, n);
        for (i = n-1; i > 0; i--) {
            randomNr = rand();
            randomNr = randomNr % i;
            if (randomNr == 0) {
                randomNr++;
            }
            deleteBSTnode(root, randomNr, n);
        }

    }

    p.createGroup("All comp", "TotalOperations - Build", "TotalOperations - Delete", "TotalOperations - Select");

    p.showReport();
}


int main()
{
    
    demoFirst();

    perf();

    return 0;
}
