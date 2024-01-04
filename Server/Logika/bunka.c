#include <stdio.h>





typedef enum {
    LUKA,
    LES,
    SKALA,
    VODA,
    POZIAR,
    ZHORENA,
    TYPY_BUNKY_COUNT // Pomocná hodnota na určenie počtu typov
} TYPBUNKY;

static const char TYPY_BUNKY_ZNAKY[TYPY_BUNKY_COUNT] = {'U', 'L', 'S', 'V', 'P', 'Z'};



TYPBUNKY typ_bunky_get_typ_podla_charu(char znak) {
    switch (znak) {
        case 'U':
            return LUKA;
        case 'L':
            return LES;
        case 'S':
            return SKALA;
        case 'V':
            return VODA;
        case 'P':
            return POZIAR;
        case 'Z':
            return ZHORENA;
    }
    return LUKA;
}


typedef struct bunka {
    TYPBUNKY typ;
    int r;
    int s;
    int kolkoKrokovHorela;
} BUNKA;

void bunka_init(BUNKA* bunka, TYPBUNKY typ, int r, int s) {
    bunka->typ = typ;
    bunka->r = r;
    bunka->s = s;
    bunka->kolkoKrokovHorela = 0;
}

void bunka_copy_init(BUNKA* dest, BUNKA* src) {
    dest->typ = src->typ;
    dest->r = src->r;
    dest->s = src->s;
    dest->kolkoKrokovHorela = src->kolkoKrokovHorela;
}


void bunka_init_with_char(BUNKA* bunka, char typChar, int r, int s) {
    bunka->r = r;
    bunka->s = s;
    bunka->typ = typ_bunky_get_typ_podla_charu(typChar);
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

_Bool aktualizujSa(BUNKA* bunka) {
    if (bunka->typ == POZIAR) {
        bunka->kolkoKrokovHorela++;
        return 1;
    }
    return 0;
}




