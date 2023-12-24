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
    simulacia_init(sim, 4, 4);
}

void simulacia_destroy(SIMULACIA* sim) {
    pole_destroy(sim->pole);
    free(sim->pole);
    sim->smerVetru = BEZVETRIE;
}

void simulacia_vypis_sa(SIMULACIA* sim) {

    pole_vypis_sa(sim->pole);
    printf("Aktualny vietor: ");
    vypis_smer_vetra(sim->smerVetru);
    printf("\n");


}



