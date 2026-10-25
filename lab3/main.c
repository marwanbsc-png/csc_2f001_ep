#include <stdio.h>
#include <stdlib.h>
#include "monster.h"
#include "macro.h"



int main(int argc, char* argv[]) {
    struct monster* tab[10]; 
    char buf[NAME_SIZE];

    for (int i=0; i<10; i++){
        snprintf( buf,  sizeof(buf), "pikachu-%i", i);
        struct monster* pikachu= create_monster (buf, 10);
        tab[i]= pikachu;
    }
        for (int i=0; i<10; i++){
        display_monster(tab[i]);

    }
        for (int i=0; i<10; i++){
            delete_monster(tab[i]);
    }


    



}