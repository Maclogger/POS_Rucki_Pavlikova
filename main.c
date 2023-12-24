#include <stdio.h>
#include "bunka.c"
#include "pole.c"
#include "simulacia.c"

int main() {
    SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vypis_sa(&sim);

    simulacia_destroy(&sim);

    return 0;
}
