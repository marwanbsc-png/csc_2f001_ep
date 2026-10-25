#include "macro.h"
#include "monster.h"

#ifndef ARMY_H
#define ARMY_H



struct army; // declare that a data structure named army exists
struct army* create_army();
void add_monster_to_army(struct army*a, struct monster* m);
void display_army(struct army* a);
void delete_army(struct army* a);

#endif