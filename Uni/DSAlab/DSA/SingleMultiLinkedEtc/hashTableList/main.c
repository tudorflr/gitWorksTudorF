#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char key[30];
    int index;
    struct node *next;
} NodeT;

typedef struct {
    NodeT *table[27];
} hashtable;

int hash_function(const char *key) {
    int hash=0;
    hash = key[0]-11;
    return hash % 27;
}

void insert(hashtable *hash_table, char *key) {
    int index = hash_function(key);
    NodeT *newNode = (NodeT*)malloc(sizeof(NodeT));
    if (newNode == NULL) {
        printf("obo");
        exit(-1);
    }
    strncpy(newNode->key, key, sizeof(newNode->key) - 1);
    newNode->key[sizeof(newNode->key) - 1] = '\0';
    newNode->index = index;
    newNode->next = NULL;
    if (hash_table->table[index] == NULL)
        hash_table->table[index] = newNode;
    else {
        NodeT *current = hash_table->table[index];
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

void printhash(hashtable *hash_table) {
    for (int i = 0; i < 27; i++) {
        int ok = 0;
        NodeT *current = hash_table->table[i];
        while (current != NULL) {
            ok = 1;
            printf("%s %d ", current->key, current->index);
            current=current->next;
        }
        if (ok == 1)
            printf("\n");
    }
}

void findelem(hashtable *hash_table, char *key){
    int ok=0,cnt=0;
    while(cnt<27){
        NodeT *current = hash_table->table[cnt];
        while(current != NULL){
            if(strcmp(current->key , key) == 0){
                printf("da ");
                printf("%d", current->index);
                current=current->next;
                ok++;
                return;
            }
            current=current->next;
        }
        cnt++;
    }
    if(ok==0){
        printf("nu");
    }
}

void deleteelem(hashtable *hash_table, char *key){
    int ok=0,cnt=0;
    NodeT *scapare;
    while(cnt<27){
        NodeT *current = hash_table->table[cnt];
        if(current != NULL && strcmp(current->key , key) == 0){
            if(current->next==NULL){
                hash_table->table[cnt] = current->next;
                free(current);
                return;
            } else {
                hash_table->table[cnt] = current->next;
                free(current);
                return;
            }
        }
        while(current != NULL && current->next != NULL){
            if(strcmp(current->next->key , key) == 0){
                if(current->next->next!=NULL){
                    scapare=current->next;
                    current->next=current->next->next;
                    free(scapare);
                    return;
                } else{
                    scapare=current->next;
                    current->next=NULL;
                    free(scapare);
                    return;
                }
            }
            current=current->next;
        }
        cnt++;
    }
}

int main() {
    hashtable hash_table;
    for (int i = 0; i < 27; i++) {
        hash_table.table[i] = NULL;
    }
    insert(&hash_table, "Andi Darko");
    insert(&hash_table, "Bihari trl");
    insert(&hash_table, "Anastas Man");
    insert(&hash_table, "Anasdwastas Man");
    insert(&hash_table, "Anastadsadwass Man");
  //  insert(&hash_table, "Andi Drako");

    printhash(&hash_table);
    findelem(&hash_table, "Bihari trl");
    deleteelem(&hash_table, "Andi Darko");
    printf("\n");
    printhash(&hash_table);
    return 0;
}
