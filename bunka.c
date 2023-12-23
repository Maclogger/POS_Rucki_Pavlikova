#include <stdio.h>

typedef struct bunka {
    char znak;
    int r;
    int s;
} BUNKA;

void bunka_init(BUNKA* bunka, char znak, int r, int s) {
    bunka->znak = znak;
    bunka->r = r;
    bunka->s = s;
}

void bunka_destroy(BUNKA* bunka) {
    bunka->znak = 0;
    bunka->r = 0;
    bunka->s = 0;
}

void bunka_vypis_sa(BUNKA* bunka) {
    printf("%c", bunka->znak);
}




