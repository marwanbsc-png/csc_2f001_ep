#include <stdio.h>
#include <stdlib.h>
#include "monster.h"
#include "macro.h"
#include "army.h"


int main(int argc, char* argv[]) {
    struct army* a= create_army();
    char buf[NAME_SIZE];


    for (int i=0; i<10; i++){
        snprintf( buf,  sizeof(buf), "pikachu-%i", i);
        struct monster* pikachu= create_monster (buf, 10);
        add_monster_to_army(a, pikachu);
    }

    display_army(a);
    delete_army(a);

}