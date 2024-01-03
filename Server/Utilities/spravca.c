#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../PosSockets/char_buffer.h"

#define RIADOK_DLZKA 50000
#define INIT_SIZE 1024

typedef struct {
    FILE* file;
    FILE* file2;
    char filename[256];
} SPRAVCA;



void spravca_init(SPRAVCA* spravca, char* filename) {
    strncpy(spravca->filename, filename, 255);
    spravca->filename[255] = '\0';
}

void spravca_destroy(SPRAVCA* spravca) {
    spravca->file = NULL;
}

_Bool uloz_novy_save(SPRAVCA* spravca, const char* line) {
    // line = "nazovSavu;cisloKroku;smerVetru;kolkoKratFukalVietor;pocetRiadkov;pocetStlpcov;S;kolkoHorelPoziar;S;kolkoHorelPoziar;V;kolkoHorelPoziar;L;kolkoHorelPoziar;L;kolkoHorelPoziar;U;kolkoHorelPoziar;...;S;kolkoHorelPoziar;V;kolkoHorelPoziar;"

    spravca->file = fopen(spravca->filename, "a+"); // a+ = append a čítanie
    if (spravca->file == NULL) {
        printf("Chyba pri otvarani suboru pri uloz_novy_save!\n");
        return 0; // Chyba pri otváraní súboru
    }

    fprintf(spravca->file, "%s\n", line); // Pridáva nový riadok na koniec každého zápisu

    // Vyprázdni buffer a zapíše dáta na disk
    fflush(spravca->file);

    fclose(spravca->file);

    return 1;

    spravca->file = fopen(spravca->filename, "r");

    printf("\nzaciatok: \n");

    char riadok[RIADOK_DLZKA];
    int i = 0;
    while (fgets(riadok, sizeof(riadok), spravca->file)) {
        printf("%d: %s", i, riadok);
        i++;
    }

    printf("\nkoniec\n");

    fclose(spravca->file);

    return 1;
}


void serializuj_nazvy_vsetkych_savov(SPRAVCA* spravca, CHAR_BUFFER* buffer) {

    char_buffer_clear(buffer);

    spravca->file = fopen(spravca->filename, "r");
    if (spravca->file == NULL) {
        printf("Chyba pri otvarani suboru pri serializuj_nazvy_vsetkych_savov!\n");
        return;
    }

    char temp[50]; // Dočasný buffer na formátovanie reťazcov

    // Pridáme číslo statusu OK
    sprintf(temp, "%d;", 0);
    char_buffer_append(buffer, temp, strlen(temp));

    char riadok[RIADOK_DLZKA];
    while (fgets(riadok, sizeof(riadok), spravca->file)) {
        char *token = strtok(riadok, ";");
        if (token != NULL) {
            sprintf(temp, "%s;", token);
            char_buffer_append(buffer, temp, strlen(temp));
        }
    }

    fclose(spravca->file);
}



void get_save_zo_suboru(SPRAVCA* spravca, const char* nazov_savu, CHAR_BUFFER* stringZoSuboru) {
    // vracia zo súboru: "nazovSavu;cisloKroku;smerVetru;kolkoKratFukalVietor;pocetRiadkov;pocetStlpcov;S;kolkoHorelPoziar;S;kolkoHorelPoziar;V;kolkoHorelPoziar;L;kolkoHorelPoziar;L;kolkoHorelPoziar;U;kolkoHorelPoziar;...;S;kolkoHorelPoziar;V;kolkoHorelPoziar;"

    char_buffer_clear(stringZoSuboru);

    spravca->file = fopen(spravca->filename, "r");
    if (spravca->file == NULL) {
        printf("Chyba pri otvarani suboru pri get_save_zo_suboru!\n");
        return;
    }

    char riadok[RIADOK_DLZKA];
    size_t dlzkaNazvuSavu = strlen(nazov_savu);
    while (fgets(riadok, sizeof(riadok), spravca->file)) {
        if (strncmp(riadok, nazov_savu, dlzkaNazvuSavu) == 0 && riadok[dlzkaNazvuSavu] == ';') {
            char_buffer_append(stringZoSuboru, riadok, strlen(riadok));
            break;
        }
    }

    fclose(spravca->file);
}

_Bool spravca_zmaz_save(SPRAVCA *spravca, char *nazovSavu) {

    spravca->file = fopen(spravca->filename, "r");
    spravca->file2 = fopen("../temp.txt", "w");

    if (!spravca->file || !spravca->file2) {
        return 0;
    }

    char riadok[RIADOK_DLZKA];
    while (fgets(riadok, sizeof(riadok), spravca->file) != NULL) {
        if (strncmp(riadok, nazovSavu, strlen(nazovSavu)) != 0 || riadok[strlen(nazovSavu)] != ';') {
            fputs(riadok, spravca->file2);
        }
    }

    fclose(spravca->file);
    fclose(spravca->file2);

    remove("../saves.txt");
    rename("../temp.txt", "../saves.txt");

    return 1;
}










