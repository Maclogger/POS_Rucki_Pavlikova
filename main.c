#include <stdio.h>
#include "bunka.c"
#include "pole.c"

int main() {


    POLE pole;
    pole_init(&pole, 10, 10);
    pole_vypis_sa(&pole);
    pole_destroy(&pole);
    return 0;
}
