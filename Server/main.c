#include <stdio.h>
#include <time.h>
#include "Logika/bunka.c"
#include "Logika/simulacia.c"

int main() {
    srand(time(NULL));

    SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vypis_sa(&sim);

    simulacia_pridaj_ohen(&sim, 0, 0);
    simulacia_pridaj_ohen(&sim, 3, 3);

    simulacia_vypis_sa(&sim);

    simulacia_destroy(&sim);
    return 0;
}


