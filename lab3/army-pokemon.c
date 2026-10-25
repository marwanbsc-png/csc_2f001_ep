#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monster.h"
#include "macro.h"
#include "army.h"

struct army {
  struct monster** monsters; // a pointer to an array, where each element of the array is a pointer to a monster
  int top;                   // where you have the last monster in the array
  int capacity;              // the capacity of the array
};


struct army* create_army(){
    struct army* a= malloc(sizeof(*a));
    a->monsters= NULL;
    a->capacity=0;
    a->top=0;
    return a;

}

void add_monster_to_army(struct army*a, struct monster* m){


    if(a->top==a->capacity){
        if (a->capacity == 0){
            a->capacity = 1;
        }

        else {
            a->capacity = a->capacity * 2;
        }

        struct monster** monsters= malloc(sizeof(*a->monsters) * a->capacity);
        memcpy(monsters,a->monsters, a->top * sizeof(*a->monsters));
        monsters[a->top ] = m;
        free(a->monsters);
        a->monsters = monsters;
        a->top+=1;  
    }
    else{
        a->monsters[a->top  ] = m;
        a->top+=1;
    }

                
}

void display_army(struct army* a){
    for(int i=0; i<a->top; i++){
        display_monster(a->monsters[i]);
    }
}

void delete_army(struct army* a){
    free(a->monsters);
    free(a);
}
