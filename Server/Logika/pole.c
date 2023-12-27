#include <stdlib.h>

typedef struct pole {
    int pocetRiadkov;
    int pocetStlpcov;
    BUNKA** bunky;
} POLE;

void pole_init(POLE* pole, int pocetRiadkov, int pocetStlpcov) {
    pole->pocetRiadkov = pocetRiadkov;
    pole->pocetStlpcov = pocetStlpcov;
    // Alokácia riadkov
    pole->bunky = (BUNKA**) calloc(pocetRiadkov, sizeof(BUNKA*));
    for (int r = 0; r < pocetRiadkov; r++) {
        // Alokácia stĺpcov v každom riadku
        pole->bunky[r] = (BUNKA*) calloc(pocetStlpcov, sizeof(BUNKA));
        for (int s = 0; s < pocetStlpcov; s++) {
            bunka_init(&pole->bunky[r][s], LES, r, s); // Inicializácia každej bunky
        }
    }
}


void pole_destroy(POLE* pole) {
    for (int r = 0; r < pole->pocetRiadkov; r++) {
        for (int s = 0; s < pole->pocetStlpcov; s++) {
            bunka_destroy(&pole->bunky[r][s]); // Uvoľnenie každej bunky
        }
        free(pole->bunky[r]); // Uvoľnenie stĺpcov v riadku
    }
    free(pole->bunky); // Uvoľnenie riadkov
}


void pole_vypis_sa(POLE* pole) {
    printf("  ");
    for (int i = 0; i < pole->pocetStlpcov; ++i) {
        printf("   %d  ", i);
    }

    printf("\n  ");
    for (int i = 0; i < pole->pocetStlpcov; ++i) {
        printf("+-----");
    }
    printf("+\n");

    for (int r = 0; r < pole->pocetRiadkov; r++) {
        printf("%d ", r);
        for (int s = 0; s < pole->pocetStlpcov; s++) {
            printf("|  ");
            bunka_vypis_sa(&pole->bunky[r][s]);
            printf("  ");
        }
        printf("|\n  ");
        for (int i = 0; i < pole->pocetStlpcov; ++i) {
            printf("+-----");
        }
        printf("+ \n");
    }
}











