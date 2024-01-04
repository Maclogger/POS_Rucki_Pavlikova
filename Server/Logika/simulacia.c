#include "vietor.c"
#include "../PosSockets/char_buffer.h"
#include "../Utilities/generator_nahody.c"

#define KOLKO_VYDRZI_OHEN 5
#define PRAVDEPODOBNOST_VETRU 25.0

typedef struct simulacia {
    POLE* pole;
    SMER smerVetru;
    int cisloKroku;
    int kolkoKratFukalVietor;
    _Bool initialized;
} SIMULACIA;

void simulacia_init(SIMULACIA* sim, int pocetRiadkov, int pocetStlpcov) {
    sim->pole = (POLE*) malloc(sizeof(POLE));
    pole_init(sim->pole, pocetRiadkov, pocetStlpcov);
    sim->smerVetru = BEZVETRIE;
    sim->cisloKroku = 0;
    sim->kolkoKratFukalVietor = 0;
    sim->initialized = 1;
}

void simulacia_init_podla_spravy_vytvorenia(SIMULACIA* sim) {
    //"pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "vytvorMapu;3;3;S;S;V;L;L;U;U;S;V;"
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
                sim->pole->bunky[r][s].kolkoKrokovHorela = 0;
            }
        }
    }
}

void simulacia_init_podla_celkoveho_stringu(SIMULACIA* sim, CHAR_BUFFER* char_buffer) {
    // "cisloKroku;smerVetru;kolkoKratFukalVietor;pocetRiadkov;pocetStlpcov;S;kolkoHorelPoziar;S;kolkoHorelPoziar;V;kolkoHorelPoziar;L;kolkoHorelPoziar;L;kolkoHorelPoziar;U;kolkoHorelPoziar;...;S;kolkoHorelPoziar;V;kolkoHorelPoziar;"

    // cislo Kroku:
    char* token = strtok(NULL, ";");
    int cisloKroku = atoi(token);

    // smer vetru:
    token = strtok(NULL, ";");
    char smerVetru = token[0];

    // kolkokrat fukal vetrik:
    token = strtok(NULL, ";");
    int kolkoKratFukalVietor = atoi(token);

    // pocet riadkov:
    token = strtok(NULL, ";");
    int pocetRiadkov = atoi(token);

    // pocet stlpcov:
    token = strtok(NULL, ";");
    int pocetStlpcov = atoi(token);

    simulacia_init(sim, pocetRiadkov, pocetStlpcov);

    for (int r = 0; r < pocetRiadkov; r++) {
        for (int s = 0; s < pocetStlpcov; s++) {
            // typ bunky:
            token = strtok(NULL, ";");
            char typBunky = token[0];
            bunka_init_with_char(&sim->pole->bunky[r][s], typBunky, r, s);

            // pocet horeni bunky:
            token = strtok(NULL, ";");
            int kolkoHorel = atoi(token);
            sim->pole->bunky[r][s].kolkoKrokovHorela = kolkoHorel;
        }
    }

    sim->cisloKroku = cisloKroku;
    sim->smerVetru = get_smer_z_charu(smerVetru);
    sim->kolkoKratFukalVietor = kolkoKratFukalVietor;
}

void simulacia_destroy(SIMULACIA* sim) {
    if (sim->initialized) {
        pole_destroy(sim->pole);
        free(sim->pole);
        sim->smerVetru = BEZVETRIE;
    }
}

void simulacia_vypis_sa(SIMULACIA* sim) {
    printf("\n\n");
    pole_vypis_sa(sim->pole);
    printf("Aktualny vietor: ");
    vypis_smer_vetra(sim->smerVetru);
    printf("\n\n\n");
}

void simulacia_serializuj_sa(SIMULACIA *sim, CHAR_BUFFER* odpoved) {

    // vracia: "0;cisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"
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

void simulacia_serializuj_sa_pre_save(SIMULACIA *sim, CHAR_BUFFER* odpoved) {

    // vracia: "cisloKroku;smerVetru;kolkoKratFukalVietor;pocetRiadkov;pocetStlpcov;S;kolkoHorelPoziar;S;kolkoHorelPoziar;V;kolkoHorelPoziar;L;kolkoHorelPoziar;L;kolkoHorelPoziar;U;kolkoHorelPoziar;...;S;kolkoHorelPoziar;V;kolkoHorelPoziar;"
    // smer vetru ako char iba.

    //char_buffer_clear(odpoved);

    char temp[50]; // Dočasný buffer na formátovanie reťazcov

    // Pridáme číslo kroku
    sprintf(temp, "%d;", sim->cisloKroku);
    char_buffer_append(odpoved, temp, strlen(temp));

    // Pridáme smer vetru ako char
    temp[0] = SMER_POPISY[sim->smerVetru];
    temp[1] = ';';
    temp[2] = '\0';
    char_buffer_append(odpoved, temp, strlen(temp));

    sprintf(temp, "%d;", sim->kolkoKratFukalVietor);
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

            int kolkoHorel = sim->pole->bunky[r][s].kolkoKrokovHorela;
            sprintf(temp, "%d;", kolkoHorel);
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







typedef struct shared_data_krok {
    int pocetRiadkov;
    int pocetStlpcov;
    POLE* pole;
    POLE* kopia;
    SMER smerVetru;
    pthread_mutex_t mutex;
} SHARED_DATA_KROK;

void shared_data_krok_init(SHARED_DATA_KROK* data, POLE* pole, POLE* kopia, SMER smerVetru) {
    data->pole = pole;
    data->kopia = kopia;
    data->pocetStlpcov = pole->pocetStlpcov;
    data->pocetRiadkov = pole->pocetRiadkov;
    data->smerVetru = smerVetru;
}

typedef struct vlakno_data {
    SHARED_DATA_KROK* data;
    int r;
} VLAKNO_DATA;


void vlakno_data_init(VLAKNO_DATA* vlaknoData, int r, SHARED_DATA_KROK* data) {
    vlaknoData->r = r;
    vlaknoData->data = data;
}

void vlakno_data_destroy(VLAKNO_DATA* vlaknoData) {
    free(vlaknoData);
}





void* vykonaj_krok_riadok(void* arg) {
    VLAKNO_DATA* vlaknoData = (VLAKNO_DATA*) arg;

    for (int s = 0; s < vlaknoData->data->kopia->pocetStlpcov; s++) {
        pthread_mutex_lock(&vlaknoData->data->mutex);
        BUNKA* stredKopia = &vlaknoData->data->kopia->bunky[vlaknoData->r][s];
        BUNKA* stred = &vlaknoData->data->pole->bunky[vlaknoData->r][s];
        pthread_mutex_unlock(&vlaknoData->data->mutex);
        if (stredKopia->typ == POZIAR) {
            for (int i = 0; i < 4; i++) {
                pthread_mutex_lock(&vlaknoData->data->mutex);
                BUNKA* bunkaOkoliaKopia = getBunkuOkolia(vlaknoData->data->kopia, stredKopia, i);
                BUNKA* bunkaOkolia = getBunkuOkolia(vlaknoData->data->pole, stred, i);
                pthread_mutex_unlock(&vlaknoData->data->mutex);
                if (bunkaOkoliaKopia != NULL) {
                    // je v rámci mapy:
                    if (bunkaOkoliaKopia->typ == LES || bunkaOkoliaKopia->typ == LUKA) {
                        if (vlaknoData->data->smerVetru == BEZVETRIE) {
                            if (getRandomDouble(0.0, 100.0) < 20.0) {
                                pthread_mutex_lock(&vlaknoData->data->mutex);
                                bunkaOkolia->typ = POZIAR;
                                pthread_mutex_unlock(&vlaknoData->data->mutex);
                            }
                        } else {
                            // ak veje vietor:
                            if ((i == 0 && vlaknoData->data->smerVetru == SEVER) ||
                                (i == 1 && vlaknoData->data->smerVetru == JUH) ||
                                (i == 2 && vlaknoData->data->smerVetru == VYCHOD) ||
                                (i == 3 && vlaknoData->data->smerVetru == ZAPAD)) {
                                if (getRandomDouble(0.0, 100.0) < 90.0) {
                                    pthread_mutex_lock(&vlaknoData->data->mutex);
                                    bunkaOkolia->typ = POZIAR;
                                    pthread_mutex_unlock(&vlaknoData->data->mutex);
                                }
                            } else {
                                if (getRandomDouble(0.0, 100.0) < 2.0) {
                                    pthread_mutex_lock(&vlaknoData->data->mutex);
                                    bunkaOkolia->typ = POZIAR;
                                    pthread_mutex_unlock(&vlaknoData->data->mutex);
                                }
                            }
                        }
                    }
                }
            }
            if ((stred->kolkoKrokovHorela >= KOLKO_VYDRZI_OHEN) && (getRandomDouble(0,100.0) < 30.0)) {
                pthread_mutex_lock(&vlaknoData->data->mutex);
                stred->typ = ZHORENA;
                stred->kolkoKrokovHorela = 0;
                pthread_mutex_unlock(&vlaknoData->data->mutex);
            }
        }
        else if (stredKopia->typ == ZHORENA) {
            for (int i = 0; i < 4; i++) {
                pthread_mutex_lock(&vlaknoData->data->mutex);
                BUNKA* okolnaKopia = getBunkuOkolia(vlaknoData->data->kopia, stredKopia, i);
                pthread_mutex_unlock(&vlaknoData->data->mutex);
                if (okolnaKopia != NULL && okolnaKopia->typ == VODA) {
                    if (getRandomDouble(0.0, 100.0) < 10.0) {
                        pthread_mutex_lock(&vlaknoData->data->mutex);
                        stred->typ = LUKA;
                        pthread_mutex_unlock(&vlaknoData->data->mutex);
                    }
                    break;
                }
            }
        }
        else if (stred->typ == LUKA) {
            for (int i = 0; i < 4; i++) {
                pthread_mutex_lock(&vlaknoData->data->mutex);
                BUNKA* okolnaKopia = getBunkuOkolia(vlaknoData->data->kopia, stredKopia, i);
                pthread_mutex_unlock(&vlaknoData->data->mutex);
                if (okolnaKopia != NULL && okolnaKopia->typ == LES) {
                    if (getRandomDouble(0.0, 100.0) < 2.0) {
                        pthread_mutex_lock(&vlaknoData->data->mutex);
                        stred->typ = LES;
                        pthread_mutex_unlock(&vlaknoData->data->mutex);
                    }
                    break;
                }
            }
        }
        pthread_mutex_lock(&vlaknoData->data->mutex);
        aktualizujSa(stred);
        pthread_mutex_unlock(&vlaknoData->data->mutex);
    }
    vlakno_data_destroy(vlaknoData);
}



_Bool vykonaj_krok(SIMULACIA* sim) {
    sim->cisloKroku++;

    POLE* kopia = (POLE*)malloc(sizeof(POLE));
    pole_copy_init(kopia, sim->pole);


    pthread_t vlakna[sim->pole->pocetRiadkov];

    SHARED_DATA_KROK data;
    shared_data_krok_init(&data, sim->pole, kopia, sim->smerVetru);

    for (int r = 0; r < sim->pole->pocetRiadkov; r++) {
        VLAKNO_DATA* vlaknoData = (VLAKNO_DATA*) malloc(sizeof(VLAKNO_DATA));
        vlakno_data_init(vlaknoData, r, &data);
        pthread_create(&vlakna[r], NULL, vykonaj_krok_riadok, vlaknoData);
    }

    for (int r = 0; r < sim->pole->pocetRiadkov; r++) {
        pthread_join(vlakna[r], NULL);
    }

    // smer vetru:
    if (sim->smerVetru == BEZVETRIE) {
        if (getRandomDouble(0.0, 100.0) < PRAVDEPODOBNOST_VETRU) {
            sim->smerVetru = getRandomSmerVetru();
        }
    } else {
        if (sim->kolkoKratFukalVietor < 3) {
            sim->kolkoKratFukalVietor++;
        } else {
            if (getRandomDouble(0.0, 100.0) < PRAVDEPODOBNOST_VETRU) {
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
