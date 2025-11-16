#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int key;
    struct _NODE *next;
}NODE;

typedef struct _LIST{
    struct _NODE* first;
}LIST;

LIST* create_list(){
    LIST*l=(LIST*)malloc(sizeof(LIST));
    if(!l){
        exit(-1);
    }
    l->first=0;
    return l;
}

void insert_first(LIST* l, int key){
    NODE* n = calloc(1, sizeof(NODE));
    if(!n){
        exit(-1);
    }
    n->key=key;

    n->next=l->first;
    l->first=n;
}

void delete_first(LIST* l){
    if(!l->first){
        return;
    }
    NODE*n=l->first->next;
    free(l->first);
    l->first=n;
}

void delete_elem(LIST*l, int key){
    if(l->first->key==key){
        delete_first(l);
        return;
    }

    NODE*current = l->first;
    NODE*prev = 0;
    while(current){
        if(current->key==key){
            prev->next=current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void print_list(LIST*l){
    NODE*n=l->first;
    while(n){
        printf("%d ", n->key);
        n=n->next;
    }
    printf("\n");
}

void show_trucks(LIST*l){
    print_list(l);
}

int list_contains(LIST*l, int key){
    NODE*n=l->first;
    while(n){
        if(n->key==key){
            return 1;
        }
        n=n->next;
    }
    return 0;
}

void on_road(LIST* road, int truck_id){
    insert_first(road, truck_id);
}

int enter_garage(LIST* road, LIST* garage, int truck_id){
   if(!list_contains(road, truck_id)){
        return -1;
   }
   delete_elem(road, truck_id);
   insert_first(garage, truck_id);
   //return 1;
}

int exit_garage(LIST* garage, int truck_id){
    if(
        garage->first &&
        garage->first->key==truck_id
    ){
        delete_first(garage);
        return 1;
    }
    return 0;
}

int main()
{
    LIST* road = create_list();
    LIST* garage = create_list();
    on_road(road, 1);
    on_road(road, 2);
    on_road(road, 3);
    printf("Trucks on the road: ");
    show_trucks(road);
    enter_garage(road, garage, 2);
    printf("Trucks on the road after moving truck 2 to the garage: ");
    show_trucks(road);
    printf("Trucks in the garage: ");
    show_trucks(garage);
    int truck_id = 3;
    if (exit_garage(garage, truck_id)) {
        printf("Truck %d exited from the garage.\n", truck_id);
    } else {
        printf("Truck %d not found in the garage.\n", truck_id);
    }
    printf("Trucks in the garage after truck %d exited: ", truck_id);
    show_trucks(garage);


    return 0;
}
