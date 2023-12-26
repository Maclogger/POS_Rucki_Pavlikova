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
    nastav_pravdepodobnosti(&sim->p, 25, 25, 25, 25);
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

void simulacia_vytvor_nahodnu_mapu(SIMULACIA *sim) {
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


