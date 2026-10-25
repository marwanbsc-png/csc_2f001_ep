#include "monster.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "macro.h"

struct monster* create_monster (char name[NAME_SIZE], int life_points){
    struct monster* m = malloc(sizeof(*m));
    m->life_points = life_points;
    strncpy(m->name, name, NAME_SIZE);
    return m;
}



void display_monster(struct monster* n){
    printf("name of the monster is %s and it has %i life points\n", n->name, n->life_points);

}

void delete_monster(struct monster* m){
    free(m);

}