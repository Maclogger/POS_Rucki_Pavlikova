#include "vietor.c"

typedef struct simulacia {
    POLE* pole;
    SMER smerVetru;
} SIMULACIA;

void simulacia_init(SIMULACIA* sim, int pocetRiadkov, int pocetStlpcov) {
    sim->pole = (POLE*) malloc(sizeof(POLE));
    pole_init(sim->pole, pocetRiadkov, pocetStlpcov);
    sim->smerVetru = BEZVETRIE;
}

void simulacia_init_default(SIMULACIA* sim) {
    printf("\n      Simulacia POZIAR\n");
    printf("          Vytvoril:\n");
    printf("Agata Pavlikova & Marek Rucki\n\n");
    simulacia_init(sim, 5, 5);
}

void simulacia_destroy(SIMULACIA* sim) {
    pole_destroy(sim->pole);
    free(sim->pole);
    sim->smerVetru = BEZVETRIE;
}

void simulacia_vypis_sa(SIMULACIA* sim) {
    printf("\n\n");
    pole_vypis_sa(sim->pole);
    printf("Aktualny vietor: ");
    vypis_smer_vetra(sim->smerVetru);
    printf("\n\n\n");
}

_Bool simulacia_pridaj_ohen(SIMULACIA* sim, int r, int s) {
    if (r < 0 || r >= sim->pole->pocetRiadkov || s < 0 || s >= sim->pole->pocetStlpcov) {
        printf("Bunka [%d, %d] je MIMO ROZSAH!!!\n", r, s);
        return 0;
    }

    if (sim->pole->bunky[r][s].typ == SKALA) {
        printf("Na bunke [%d, %d] nemozete zalozit poziar! To je skala!\n", r, s);
        return 0;
    }
    if (sim->pole->bunky[r][s].typ == POZIAR) {
        printf("V bunke [%d, %d] sa uz poziar nachadza!\n", r, s);
        return 0;
    }
    bunka_init(&sim->pole->bunky[r][s], POZIAR, r, s);
    return 1;
}


