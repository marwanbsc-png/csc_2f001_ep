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

    if (a->top ==0){
        a->first_node = next_node;
    }
    else{
        struct node* cur = a->first_node;
        for(int i=1; i<a->top; i++){
            cur= cur->next;
        }
        cur->next= next_node;
    }
    a->top+=1;          
}

void display_army(struct army* a){
    printf("This is a %i stars army\n", a->stars);
    struct node* cur= a->first_node;
    for(int i=0; i<a->top; i++){
        display_monster(cur->monster);
        cur= cur-> next;
    }
}

void delete_army(struct army* a){
    free(a);
}
