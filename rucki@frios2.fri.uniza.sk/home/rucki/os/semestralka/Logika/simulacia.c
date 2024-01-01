#include "vietor.c"
#include "../PosSockets/char_buffer.h"
#include "../Utilities/generator_nahody.c"

typedef struct simulacia {
    POLE* pole;
    SMER smerVetru;
    int cisloKroku;
    int kolkoKratFukalVietor;


} SIMULACIA;

void simulacia_init(SIMULACIA* sim, int pocetRiadkov, int pocetStlpcov) {
    sim->pole = (POLE*) malloc(sizeof(POLE));
    pole_init(sim->pole, pocetRiadkov, pocetStlpcov);
    sim->smerVetru = BEZVETRIE;
    sim->cisloKroku = 0;
    sim->kolkoKratFukalVietor = 0;
}

void simulacia_init_podla_spravy_vytvorenia(SIMULACIA* sim) {

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

void simulacia_init_podla_savu(SIMULACIA* sim, CHAR_BUFFER* char_buffer) {
    //"priklad;0;B;5;5;L;S;L;V;S;U;U;V;V;S;L;V;S;S;U;L;L;U;L;L;V;U;L;L;L;\n"

    strtok(char_buffer->data, ";");

    char* token = strtok(NULL, ";");
    sim->cisloKroku = atoi(token);

    token = strtok(NULL, ";");
    char smerVetru = token[0];
    sim->smerVetru = get_smer_z_charu(smerVetru);

    simulacia_init_podla_spravy_vytvorenia(sim);
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

    // vracia: "cisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"
    // smer vetru ako char iba.

    //char_buffer_clear(odpoved);

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


BUNKA* getBunkuOkolia(POLE* pole, BUNKA* stred, int poradoveCislo) {

    int rStred = stred->r;
    int sStred = stred->s;

    switch(poradoveCislo) {
        case 0: {
            // hore
            if (rStred - 1 >= 0) {
                return &pole->bunky[rStred - 1][sStred];
            }
        }
        case 1: {
            // dole
            if (rStred + 1 < pole->pocetRiadkov) {
                return &pole->bunky[rStred + 1][sStred];
            }
        }
        case 2: {
            // doprava
            if (sStred + 1 < pole->pocetStlpcov) {
                return &pole->bunky[rStred][sStred + 1];
            }
        }
        case 3: {
            // doľava
            if (sStred - 1 >= 0) {
                return &pole->bunky[rStred][sStred - 1];
            }
        }
    }
    return NULL;
}



_Bool vykonaj_krok(SIMULACIA* sim) {
    sim->cisloKroku++;

    POLE* kopia = (POLE*)malloc(sizeof(POLE));
    pole_copy(kopia, sim->pole);


    // požiar a zhorene:
    for (int r = 0; r < kopia->pocetRiadkov; r++) {
        for (int s = 0; s < kopia->pocetStlpcov; s++) {
            BUNKA* stredKopia = &kopia->bunky[r][s];
            BUNKA* stred = &sim->pole->bunky[r][s];
            if (stredKopia->typ == POZIAR) {
                for (int i = 0; i < 4; i++) {
                    BUNKA* bunkaOkoliaKopia = getBunkuOkolia(kopia, stredKopia, i);
                    BUNKA* bunkaOkolia = getBunkuOkolia(sim->pole, stred, i);
                    if (bunkaOkoliaKopia != NULL) {
                        // je v rámci mapy:
                        if (bunkaOkoliaKopia->typ == LES || bunkaOkoliaKopia->typ == LUKA) {
                            if (sim->smerVetru == BEZVETRIE) {
                                if (getRandomDouble(0.0, 100.0) < 20.0) {
                                    bunkaOkolia->typ = POZIAR;
                                }
                            } else {
                                // ak veje vietor:
                                if ((i == 0 && sim->smerVetru == SEVER) ||
                                        (i == 1 && sim->smerVetru == JUH) ||
                                        (i == 2 && sim->smerVetru == VYCHOD) ||
                                        (i == 3 && sim->smerVetru == ZAPAD)) {

                                    if (getRandomDouble(0.0, 100.0) < 90.0) {
                                        bunkaOkolia->typ = POZIAR;
                                    }
                                } else {
                                    if (getRandomDouble(0.0, 100.0) < 2.0) {
                                        bunkaOkolia->typ = POZIAR;
                                    }
                                }
                            }
                        }
                    }
                }
                stred->typ = ZHORENA;
            }
            else if (stredKopia->typ == ZHORENA) {
                for (int i = 0; i < 4; i++) {
                    BUNKA* okolnaKopia = getBunkuOkolia(kopia, stredKopia, i);
                    if (okolnaKopia != NULL && okolnaKopia->typ == VODA) {
                        if (getRandomDouble(0.0, 100.0) < 10.0) {
                            stred->typ = LUKA;
                        }
                        break;
                    }
                }
            }
            else if (stred->typ == LUKA) {
                for (int i = 0; i < 4; i++) {
                    BUNKA* okolnaKopia = getBunkuOkolia(kopia, stredKopia, i);
                    if (okolnaKopia != NULL && okolnaKopia->typ == LES) {
                        if (getRandomDouble(0.0, 100.0) < 2.0) {
                            stred->typ = LES;
                        }
                        break;
                    }
                }
            }
        }
    }

    // smer vetru:
    if (sim->smerVetru == BEZVETRIE) {
        if (getRandomDouble(0.0, 100.0) < 10.0) {
            sim->smerVetru = getRandomSmerVetru();
        }
    } else {
        if (sim->kolkoKratFukalVietor < 3) {
            sim->kolkoKratFukalVietor++;
        } else {
            if (getRandomDouble(0.0, 100.0) < 10.0) {
                SMER novySmer = getRandomSmerVetru();
                if (novySmer == sim->smerVetru) {
                    sim->kolkoKratFukalVietor++;
                } else {
                    sim->kolkoKratFukalVietor = 0;
                }
            } else {
                sim->smerVetru = BEZVETRIE;
                sim->kolkoKratFukalVietor = 0;
            }
        }
    }
    pole_destroy(kopia);
    free(kopia);
    return 1;
}
