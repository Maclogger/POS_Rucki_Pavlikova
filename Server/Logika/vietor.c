#include "pole.c"


typedef enum {
    SEVER,
    VYCHOD,
    JUH,
    ZAPAD,
    BEZVETRIE,
    SMERY_COUNT // Pomocná hodnota na určenie počtu smerov
} SMER;

const char* SMER_POPISY[SMERY_COUNT] = {"Sever", "Vychod", "Juh", "Zapad", "Bezvetrie"};


int kontrola_rozsahu(int cislo, int pocetPrvkov) {
    if (cislo >= 0 && cislo < pocetPrvkov) return cislo;
    return -1;
}


int get_suradnicuR_v_smere_vetra(const SMER smerVetru, int rStart, int sStart, POLE* pole) {
    if (smerVetru == SEVER) {
        return kontrola_rozsahu(rStart - 1, pole->pocetRiadkov);
    } else if (smerVetru == JUH) {
        return kontrola_rozsahu(rStart + 1, pole->pocetRiadkov);
    }
    return rStart;
}

int get_suradnicuS_v_smere_vetra(SMER smerVetru, int rStart, int sStart, POLE* pole) {
    if (smerVetru == ZAPAD) {
        return kontrola_rozsahu(sStart - 1, pole->pocetStlpcov);
    } else if (smerVetru == VYCHOD) {
        return kontrola_rozsahu(sStart + 1, pole->pocetStlpcov);
    }
    return sStart;
}


void vypis_smer_vetra(SMER smer) {
    if (smer >= 0 && smer < SMERY_COUNT) {
        printf("%s", SMER_POPISY[smer]);
    } else {
        printf("CHYBA!!! NEPLATNY SMER VETRU!\n");
    }
}
