#include <stdio.h>
#include "bunka.c"
#include "pole.c"

int main() {
    POLE pole;
    pole_init(&pole, 5, 4);
    pole_vypis_sa(&pole);
    //pole_zmen_policko(&pole, 0, 0);


    pole_destroy(&pole);
    return 0;
}
