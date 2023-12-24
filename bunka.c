#include <stdio.h>


typedef enum {
    LES,
    LUKA,
    SKALA,
    VODA,
    POZIAR,
    ZHORENA,
    TYPY_BUNKY_COUNT // Pomocná hodnota na určenie počtu typov
} TYPBUNKY;

static const char TYPY_BUNKY_ZNAKY[TYPY_BUNKY_COUNT] = {'L', 'U', 'S', 'V', 'P', 'Z'};


typedef struct bunka {
    TYPBUNKY typ;
    int r;
    int s;
} BUNKA;

void bunka_init(BUNKA* bunka, TYPBUNKY typ, int r, int s) {
    bunka->typ = typ;
    bunka->r = r;
    bunka->s = s;
}

void bunka_destroy(BUNKA* bunka) {
    bunka->typ = LES;
    bunka->r = 0;
    bunka->s = 0;
}

void bunka_vypis_sa(BUNKA* bunka) {
    if (bunka->typ >= 0 && bunka->typ < TYPY_BUNKY_COUNT) {
        printf("%c", TYPY_BUNKY_ZNAKY[bunka->typ]);
    } else {
        printf("?");
    }
}




