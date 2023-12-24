#include <stdio.h>
#include "bunka.c"
#include "pole.c"
#include "simulacia.c"

void simulacia_vytvor_nahodnu_mapu(SIMULACIA *sim);

int main() {
    SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vytvor_nahodnu_mapu(&sim);

    simulacia_vypis_sa(&sim);




    simulacia_destroy(&sim);
    return 0;
}


