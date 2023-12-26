//
// Created by agata on 26. 12. 2023.
//

#include "Simulacia.h"

Simulacia::Simulacia(int pocetRiadkov, int pocetStlpcov) {
    this->pocetRiadkov  = pocetRiadkov;
    this->pocetStlpcov = pocetStlpcov;

    this->pole = static_cast<char **>(calloc(pocetRiadkov, sizeof(char *)));
    for (int r = 0; r < pocetRiadkov; r++) {
        // Alokácia stĺpcov v každom riadku
        this->pole[r] = (char*) calloc(pocetStlpcov, sizeof(char));
        for (int s = 0; s < pocetStlpcov; s++) {
            this->pole[r][s]= 'U'; // Inicializácia každej bunky
        }
    }
}



Simulacia::~Simulacia() {
    for (int r = 0; r < this->pocetRiadkov; r++) {
        for (int s = 0; s < this->pocetStlpcov; s++) {
            this->pole[r][s] = 0; // Uvoľnenie každej bunky
        }
        free(this->pole[r]); // Uvoľnenie stĺpcov v riadku
    }
    free(this->pole); // Uvoľnenie riadkov
}

void Simulacia::vypisSa() {

    cout << "  ";
    for (int i = 0; i < this->pocetStlpcov; ++i) {
        cout << "   " << i << "  ";
    }
    cout << "\n  ";
    for (int i = 0; i < this->pocetStlpcov; ++i) {
        cout << "+-----";
    }
    cout << "+\n";
    for (int r = 0; r < this->pocetRiadkov; r++) {
        cout << r << " ";
        for (int s = 0; s < this->pocetStlpcov; s++) {
            cout << "|  " << this->pole[r][s] << "  ";
        }
        cout << "|\n  ";
        for (int i = 0; i < this->pocetStlpcov; ++i) {
            cout << "+-----";
        }
        cout << "+ \n";
    }
}


