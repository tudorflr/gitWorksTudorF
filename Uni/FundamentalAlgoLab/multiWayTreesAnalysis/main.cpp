/**
* @author Florea Tudor
* @group 30425
*
* lab06 - Multi way trees
*
*   Iterative and recursive have the same number of operations/calls baisically
* 
*   All of the T: I used a stack for additional memory for all of them,
*   a while which goes until the stack is emptied, and inserted elements
*   in it at each step, which means that the algorttihm goes through
*   all of the trees in linea o(n) time, because it visits every node
*   only once.
*
*
*/

#include <iostream>
#include "Profiler.h"
#include <stdlib.h>
#include <time.h>
#include <stack>

Profiler p("lab06");

using namespace std;

typedef struct node {
    int number;
    struct node* left;
    struct node* right;
} NodeT;

NodeT* createBTnode(NodeT* BT, int nr, int dir) {
    NodeT* newNode = new NodeT(); 
    newNode->number = nr;
    newNode->left = NULL;
    newNode->right = NULL;

    if (dir == 0) { 
        BT->left = newNode;
    }
    else { 
        BT->right = newNode;
    }
    return newNode;
}

void buildBT(NodeT* BT, int a[], int n) {
    int i, ok, dir = 0;
    NodeT* aux = BT;
    i = 1;

    srand(time(NULL));

    while (i < n) {
        ok = 1;
        while (ok == 1) {
            dir = rand();
            dir = dir % 2;
            if (dir == 0) {
                if (aux->left == NULL) {
                    createBTnode(aux, a[i], 0);
                    ok = 0;
                    aux = BT;
                }
                else {
                    aux = aux->left;
                }
            }
            else {
                if (aux->right == NULL) {
                    createBTnode(aux, a[i], 1);
                    ok = 0;
                    aux = BT;
                }
                else {
                    aux = aux->right;
                }
            }
        }
        i++;
    }

}

void preOrderTraversalRecTest(NodeT* BT, int testPos) {
    if (BT == NULL) {
        return;
    }

    cout << BT->number << " - " << testPos << "    ";
    preOrderTraversalRecTest(BT->left, testPos + 1);
    preOrderTraversalRecTest(BT->right, testPos + 1);
}


void preOrderTraversalIterTest(node* root)
{
    stack<node*> stackIter;
    stackIter.push(root);

    while (stackIter.empty() == false) {
        struct node* aux = stackIter.top();
        cout << aux->number << " ";
        stackIter.pop();

        if (aux->right != NULL) {
            stackIter.push(aux->right);
        }
        if (aux->left != NULL) {
            stackIter.push(aux->left);
        }
    }
}

void preOrderTraversalRec(NodeT* BT, int treeSize) {
    Operation ops = p.createOperation("TraversalRec - preOrder", treeSize);
    if (BT == NULL) {
        return;
    }

    //cout << BT->number;
    ops.count();
    preOrderTraversalRec(BT->left, treeSize);
    preOrderTraversalRec(BT->right, treeSize);
}


void preOrderTraversalIter(node* root, int treeSize)
{
    Operation ops = p.createOperation("TraversalIter - preOrder", treeSize);
    stack<node*> stackIter;
    stackIter.push(root);

    while (stackIter.empty() == false) {
        struct node* aux = stackIter.top();
        //cout << aux->number << " ";
        stackIter.pop();

        ops.count();

        if (aux->right != NULL) {
            stackIter.push(aux->right);
        }
        if (aux->left != NULL) {
            stackIter.push(aux->left);
        }
    }
}


void demoBT() {
    int a[10] = { 15, 12, 19, 22, 53, 49, 30, 100, 89, 55 };
    int n = 10;
    int i = 0; 

    NodeT* root = new NodeT();
    root->number = a[0];
    root->left = nullptr;
    root->right = nullptr;

    buildBT(root, a, n);

    cout << "Rec - demo :";
    preOrderTraversalRecTest(root, 0);
    cout << endl;
    cout << "Iterative - demo :";
    preOrderTraversalIterTest(root);
    
}


void perfRecVSIter() {
    NodeT* root = new NodeT();

    int a[10000];
    int n;

    for (n = 100; n <= 1000; n += 100) {
        
        FillRandomArray(a, n, 5, 50000, false, 0);

        root->number = a[0];
        root->left = nullptr;
        root->right = nullptr;

        buildBT(root, a, n);

        preOrderTraversalRec(root, n);

        preOrderTraversalIter(root, n);
  
    }

    p.createGroup("Rec VS Iter - preOrder", "TraversalRec - preOrder", "TraversalIter - preOrder");

    p.showReport();
}


void demoPrettyPrintR1() {
    //int a[15] = { 9, 2, 7 ,5, 2, 7, 7, -1, 5, 2, 8, 4, 9, 9, 4 };
    int a[10] = { 9, 2, 7 ,5, 2, 7, 7, -1, 5, 2 };
    int i = 0, j = 0, aux, auxPos, n = 10;

    while (a[i] != -1) {
        i++;
    }

    stack<int> stackPretty;
    stack<int> stackSpaces;

    stackPretty.push(i);
    stackSpaces.push(1);

    cout << endl << "R1 - pretty print :";

    while (stackPretty.empty() == false) {
        aux = stackPretty.top();
        auxPos = stackSpaces.top();
        stackPretty.pop();
        stackSpaces.pop();

        cout << endl;
        for (j = 0; j < auxPos; j++) {
            cout << "   ";
        }
        cout << aux; 

        for (i = 0; i < n; i++) {
            if (a[i] == aux) {
                stackPretty.push(i);
                stackSpaces.push(auxPos + 1);
            }
        }
    }

}


typedef struct nodeT1 {
    int number;
    struct nodeT1* next;
    struct nodeT1* root;
} NodeT1;

NodeT1* createT1node(NodeT1* BT, NodeT1* root, int nr, int yesORno) {
    NodeT1* newNode = new NodeT1();
    if (yesORno == 1) {
        newNode->number = nr;
        newNode->next = NULL;
        newNode->root = newNode;
    }
    else {
        newNode->number = nr;
        newNode->next = NULL;
        newNode->root = root;
    }
    return newNode;
}


typedef struct nodeT1F {
    int number;
    struct nodeT1F* child[100];

} NodeT1F;


NodeT1F* createT1nodeFinal(NodeT1F* BT, int nr) {
    NodeT1F* newNode = new NodeT1F();
    int i = 0;
    
    newNode->number = nr;
    for (i = 0; i < 10; i++) {
        newNode->child[i] = NULL;
    }
        
    return newNode;
}


void prettyPrintR2(NodeT1F *root) {
    int i = 0, j = 0, auxPos, n = 10;

    stack<NodeT1F*> stackPrettyR2;
    stack<int> stackSpacesR2;

    stackPrettyR2.push(root);
    stackSpacesR2.push(1);

    cout << endl << "R2 - pretty print :";

    while (stackPrettyR2.empty() == false) {
        NodeT1F* aux = stackPrettyR2.top();
        auxPos = stackSpacesR2.top();
        stackPrettyR2.pop();
        stackSpacesR2.pop();

        cout << endl;
        for (j = 0; j < auxPos; j++) {
            cout << "   ";
        }
        cout << aux->number;

        i = 0;
        while (aux->child[i] != NULL) {
            stackPrettyR2.push(aux->child[i]);
            stackSpacesR2.push(auxPos + 1);
            i++;
        }
    }
}


// ex5

typedef struct nodeT2 {
    int number;
    struct nodeT2* next;  // brother
    struct nodeT2* child;
} NodeT2;


NodeT2* createT2(NodeT2* BT, int nr) {
    NodeT2* newNode = new NodeT2();

    newNode->number = nr;
    newNode->next = NULL;
    newNode->child = NULL;

    return newNode;
}


void prettyPrintR3(NodeT2* root) {
    int i = 0, j = 0, auxPos, n = 10, auxYesORNo = 1;

    stack<NodeT2*> stackPrettyR3;
    stack<int> stackSpacesR3;
    stack<int> stackAddAgain;

    stackPrettyR3.push(root);
    stackSpacesR3.push(1);
    stackAddAgain.push(1);
    

    cout << endl << "R3 - pretty print :";

    while (stackPrettyR3.empty() == false) {
        NodeT2* aux = stackPrettyR3.top();
        NodeT2* auxChild = stackPrettyR3.top();
        auxPos = stackSpacesR3.top();
        auxYesORNo = stackAddAgain.top();
        stackPrettyR3.pop();
        stackSpacesR3.pop();
        stackAddAgain.pop();

        cout << endl;
        for (j = 0; j < auxPos; j++) {
            cout << "   ";
        }
        cout << aux->number;


        if (auxYesORNo == 1) {
            aux = aux->next;
            while (aux != NULL) {
                stackPrettyR3.push(aux);
                stackSpacesR3.push(auxPos);
                stackAddAgain.push(0);
                aux = aux->next;
            }
        }

        if (auxChild->child != NULL) {
            stackPrettyR3.push(auxChild->child);
            stackSpacesR3.push(auxPos + 1);
            stackAddAgain.push(1);
        }

    }
}


void T2andR3(NodeT1F* rootInit) {
    int i = 0, j = 0, auxPos, n = 15;
    NodeT2* List = new NodeT2();

    cout << endl << endl;
    NodeT1F* aux = rootInit;
    NodeT2* root = createT2(List, rootInit->number);

    stack<nodeT2*> stackFinal;
    stackFinal.push(root);
    stack<nodeT1F*> stackConvT2;
    stackConvT2.push(rootInit);

    while (stackConvT2.empty() == false) {
        NodeT1F* auxi = stackConvT2.top();
        stackConvT2.pop();
        //cout << auxi->number << " ";
        NodeT2* auxiliary = stackFinal.top();
        stackFinal.pop();


        if (auxi->child[0] != NULL) {
            auxiliary->child = createT2(auxiliary->child, auxi->child[0]->number);
            auxiliary = auxiliary->child;
            stackFinal.push(auxiliary);
            stackConvT2.push(auxi->child[0]);
            i = 1;
            while (auxi->child[i] != NULL) {
                auxiliary->next = createT2(auxiliary->next, auxi->child[i]->number);
                stackFinal.push(auxiliary->next);
                stackConvT2.push(auxi->child[i]);
                auxiliary = auxiliary->next;
                i++;
            }
        }

    }

    //cout << endl << endl;
    //cout << root->child->next->next->number;   // works / this was just for test
    //cout << "  ";
    //cout << root->child->next->child->number;
    //cout << root->child->number;

    prettyPrintR3(root);

}

// back to ex 4

void T1andR2() {
    //int a[15] = { 9, 2, 7 ,5, 2, 7, 7, -1, 5, 2, 8, 4, 9, 9, 4 };
    int a[10] = { 9, 2, 7 ,5, 2, 7, 7, -1, 5, 2 };
    int i = 0, j = 0, aux, auxPos, n = 10;
    NodeT1* List[100];
    NodeT1F* MT = new NodeT1F;
    for (i = 0; i < 100; i++) {
        List[i] = NULL;
    }

    for (i = 0; i < n; i++) {
        if (a[i] != -1) {
            if (List[a[i]] == NULL) {
                List[a[i]] = createT1node(List[a[i]], List[a[i]], i, 1);
            }
            else {
                List[a[i]]->next = createT1node(List[a[i]], List[a[i]]->root, i, 0);
                List[a[i]] = List[a[i]]->next;
            }
        }
    }

    i = 0;
    while (a[i] != -1) {
        i++;
    }
    
    NodeT1F* root = createT1nodeFinal(MT, i);

    stack<int> stackConv;
    stackConv.push(i);

    stack<nodeT1F*> stackConvNode;
    stackConvNode.push(root);
    
    while (stackConv.empty() == false) {
        aux = stackConv.top();
        stackConv.pop();
        NodeT1F* auxi = stackConvNode.top();
        stackConvNode.pop();
        //cout << aux << " ";

        if (List[aux] != NULL) {
            List[aux] = List[aux]->root;
            i = 0;
            while (List[aux] != NULL) {
                auxi->child[i] = createT1nodeFinal(auxi->child[i], List[aux]->number);
                stackConv.push(List[aux]->number);
                stackConvNode.push(auxi->child[i]);
                List[aux] = List[aux]->next;
                i++;
            }
        }

    }
    
    prettyPrintR2(root);

    T2andR3(root);

}



int main() {
   

    demoBT();

    perfRecVSIter();

    demoPrettyPrintR1();

    T1andR2();

    //T2andR3(); // in T1andR2

    return 0;
}
