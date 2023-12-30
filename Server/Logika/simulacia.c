#include "vietor.c"
#include "../PosSockets/char_buffer.h"

typedef struct simulacia {
    POLE* pole;
    SMER smerVetru;
    int cisloKroku;
} SIMULACIA;

void simulacia_init(SIMULACIA* sim, int pocetRiadkov, int pocetStlpcov) {
    sim->pole = (POLE*) malloc(sizeof(POLE));
    pole_init(sim->pole, pocetRiadkov, pocetStlpcov);
    sim->smerVetru = BEZVETRIE;
    sim->cisloKroku = 0;
}

void simulacia_init_podla_spravy(SIMULACIA* sim) {
    char* token = strtok(NULL, ";");
    int pocetRiadkov = atoi(token);

    token = strtok(NULL, ";");
    int pocetStlpcov = atoi(token);

    simulacia_init(sim, pocetRiadkov, pocetStlpcov);

    // Načítame prvky mapy
    for (int r = 0; r < pocetRiadkov; r++) {
        for (int s = 0; s < pocetStlpcov; s++) {
            token = strtok(NULL, ";");
            if (token != NULL) {
                char prvok = token[0]; // Predpokladáme, že každý prvok je jeden znak
                bunka_init_with_char(&sim->pole->bunky[r][s], prvok, r, s);
            }
        }
    }
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

void simulacia_serializuj_sa(SIMULACIA *sim, CHAR_BUFFER* odpoved) {

    // malo by vrátiť: "cisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"
    // smer vetru ako char iba.
    // pocetRiadkov = sim->pocetRiadkov;
    // pocetStlpcov = sim->pocetStlpcov;
    // na získanie znaku podľa typu bunky sa dá použiť: TYPY_BUNKY_ZNAKY[bunka->typ]
    // pričom bunka je sim->pole->bunky[r][s]

    char_buffer_clear(odpoved);

    char temp[50]; // Dočasný buffer na formátovanie reťazcov

    // Pridáme čislo statusu OK

    sprintf(temp, "%d;", 0);
    char_buffer_append(odpoved, temp, strlen(temp));

    // Pridáme číslo kroku
    sprintf(temp, "%d;", sim->cisloKroku);
    char_buffer_append(odpoved, temp, strlen(temp));

    // Pridáme smer vetru ako char
    temp[0] = SMER_POPISY[sim->smerVetru];
    temp[1] = ';';
    temp[2] = '\0';
    char_buffer_append(odpoved, temp, strlen(temp));

    // Pridáme počet riadkov a stĺpcov
    sprintf(temp, "%d;%d;", sim->pole->pocetRiadkov, sim->pole->pocetStlpcov);
    char_buffer_append(odpoved, temp, strlen(temp));

    // Pridáme znaky pre jednotlivé bunky
    for (int r = 0; r < sim->pole->pocetRiadkov; r++) {
        for (int s = 0; s < sim->pole->pocetStlpcov; s++) {
            int typBunky = sim->pole->bunky[r][s].typ;
            sprintf(temp, "%c;", TYPY_BUNKY_ZNAKY[typBunky]);
            char_buffer_append(odpoved, temp, strlen(temp));
        }
    }
}

void simulacia_pridaj_ohen(SIMULACIA* sim) {
    char* token = strtok(NULL, ";");
    int r = atoi(token);

    token = strtok(NULL, ";");
    int s = atoi(token);

    bunka_init(&sim->pole->bunky[r][s], POZIAR, r, s);
}

_Bool vykonaj_krok(SIMULACIA* sim) {
    sim->cisloKroku++;
    // TODO Vykonanie kroku simulacie podla pravidiel definovanych v zadani
    return 1;
}
