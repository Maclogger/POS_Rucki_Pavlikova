#include <time.h>
#include "vietor.c"
#include "pravdepodobnosti.c"


typedef struct simulacia {
    POLE* pole;
    SMER smerVetru;
    PRAVDEPODOBNOSTI p;
} SIMULACIA;

void simulacia_init(SIMULACIA* sim, int pocetRiadkov, int pocetStlpcov) {
    sim->pole = (POLE*) malloc(sizeof(POLE));
    pole_init(sim->pole, pocetRiadkov, pocetStlpcov);
    sim->smerVetru = BEZVETRIE;
    nastav_pravdepodobnosti(&sim->p, 80, 5, 5, 5);
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
    pole_vypis_sa(sim->pole);
    printf("Aktualny vietor: ");
    vypis_smer_vetra(sim->smerVetru);
    printf("\n");
}


void simulacia_vytvor_nahodnu_mapu(SIMULACIA *sim) {
    srand(time(NULL)); // Inicializácia generátora náhodných čísel
    for (int r = 0; r < sim->pole->pocetRiadkov; r++) {
        for (int s = 0; s < sim->pole->pocetStlpcov; s++) {
            int nahodneCislo = rand() % 100; // Generuje číslo od 0 do 99

            TYPBUNKY typ;
            if (nahodneCislo < sim->p.lesPrav) {
                typ = LES;
            } else if (nahodneCislo < sim->p.lesPrav + sim->p.lukaPrav) {
                typ = LUKA;
            } else if (nahodneCislo < sim->p.lesPrav + sim->p.lukaPrav + sim->p.skalaPrav) {
                typ = SKALA;
            } else {
                typ = VODA;
            }
            bunka_init(&sim->pole->bunky[r][s], typ, r, s);
        }
    }

}
