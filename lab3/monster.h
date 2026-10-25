#ifndef MONSTER_H
#define MONSTER_H

#include "macro.h"

struct monster{
    int life_points;
    char name[NAME_SIZE];
};

struct monster* create_monster (char name[NAME_SIZE], int life_points);
void display_monster(struct monster* point);
void delete_monster(struct monster* point);

#endif
