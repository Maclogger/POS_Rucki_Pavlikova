#include <stdlib.h>
#include "bunka.c"
#include <pthread.h>



typedef struct pole {
    int pocetRiadkov;
    int pocetStlpcov;
    BUNKA** bunky;
} POLE;




typedef struct shared_data_copy {
    BUNKA** destBunky;
    BUNKA** srcBunky;
    int r;
    int pocetStlpcov;
} SHARED_DATA_COPY;

void shared_data_init(SHARED_DATA_COPY* data, BUNKA** dest, BUNKA** src, int r, int pocetStlpcov) {
    data->destBunky = dest;
    data->srcBunky = src;
    data->r = r;
    data->pocetStlpcov = pocetStlpcov;
}

void shared_data_destroy(SHARED_DATA_COPY* data) {
    free(data);
}

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

void* skopiruj_riadok(void* arg) {
    SHARED_DATA_COPY* data = (SHARED_DATA_COPY*) arg;

    for (int s = 0; s < data->pocetStlpcov; s++) {
        bunka_copy_init(&data->destBunky[data->r][s], &data->srcBunky[data->r][s]);
    }
    shared_data_destroy(data);
    return NULL;
}



void pole_copy_init(POLE* dest, POLE* src) {
    // použité vlákna:

    dest->pocetRiadkov = src->pocetRiadkov;
    dest->pocetStlpcov = src->pocetStlpcov;

    dest->bunky = (BUNKA**) calloc(dest->pocetRiadkov, sizeof(BUNKA*));

    pthread_t vlakna[dest->pocetRiadkov];

    for (int r = 0; r < dest->pocetRiadkov; r++) {
        dest->bunky[r] = (BUNKA*) calloc(dest->pocetStlpcov, sizeof(BUNKA));
        SHARED_DATA_COPY* data = (SHARED_DATA_COPY*) malloc(sizeof(SHARED_DATA_COPY));
        shared_data_init(data, dest->bunky, src->bunky, r, dest->pocetStlpcov);
        pthread_create(&vlakna[r], NULL, skopiruj_riadok, data);
    }

    for (int r = 0; r < dest->pocetRiadkov; r++) {
        pthread_join(vlakna[r], NULL);
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











