#include "macro.h"

#ifndef MONSTER_H
#define MONSTER_H

struct monster{
    int life_points;
    char name[256];
};

struct monster* create_monster (char name[256], int life_points);
void display_monster(struct monster* point);
void delete_monster(struct monster* point);

#endif