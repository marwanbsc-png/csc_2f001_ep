#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monster.h"
#include "macro.h"
#include "army.h"

struct node {
    struct node* next;
    struct monster* monster;
};


struct army {
  struct node* first_node;
  int top;                   // where you have the last monster in the array
  int stars;
};



struct army* create_army(){
    struct army* a= malloc(sizeof(*a));
    a->first_node= NULL;
    a->top=0;
    a->stars=0;
    return a;

}

void add_monster_to_army(struct army*a, struct monster* m){

    struct node* next_node= malloc(sizeof(*next_node));
    next_node->monster=m;
    next_node->next= a->first_node;   // insert at the front: O(1), no traversal
    a->first_node= next_node;
    a->top+=1;          
}

void display_army(struct army* a){
    printf("This is a %i stars army\n", a->stars);
    struct node* cur= a->first_node;
    while(cur != NULL){
        display_monster(cur->monster);
        cur= cur->next;
    }
}

void delete_army(struct army* a){
    struct node* cur= a->first_node;
    while(cur != NULL){
        struct node* next= cur->next;
        free(cur);
        cur= next;
    }
    free(a);
}
