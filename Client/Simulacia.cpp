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
    this->vygenerujSaNahodne();
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "  ";
    for (int i = 0; i < this->pocetStlpcov; i++) {
        cout << "   " << i << "  ";
    }
    cout << endl << "  ";
    for (int i = 0; i < this->pocetStlpcov; i++) {
        cout << "+-----";
    }
    cout << "+\n";

    for (int r = 0; r < this->pocetRiadkov; r++) {
        cout << r << " ";
        for (int s = 0; s < this->pocetStlpcov; s++) {
            char znak = this->pole[r][s];

            cout << "|  ";

            // Nastavenie farby podľa hodnoty znaku
            switch (znak) {
                case 'U': SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Slabo zelená
                case 'L': SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); break; // Tmavo zelená
                case 'S': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Bledo žltá
                case 'V': SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Tmavo modrá
                case 'P': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break; // Červená
                case 'Z': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break; // Biela
                default:  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break; // Predvolená farba
            }

            cout << znak << "  ";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset na predvolenú farbu
        }
        cout << "|\n  ";
        for (int i = 0; i < this->pocetStlpcov; i++) {
            cout << "+-----";
        }
        cout << "+ \n";
    }

    // Reset farby na konci funkcie
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Simulacia::nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav) {
    this->pravdepodobnostiPolicok.nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav);
}

void Simulacia::vygenerujSaNahodne() {

    for (int r = 0; r < this->pocetRiadkov; r++) {
        for (int s = 0; s < this->pocetStlpcov; s++) {
            // Generuje číslo od 0.0 do 100.0
            double nahodneCislo = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / 100);

            char typ;
            if (nahodneCislo < this->pravdepodobnostiPolicok.getLesPrav()) {
                typ = 'L';
            } else if (nahodneCislo < this->pravdepodobnostiPolicok.getLesPrav() + this->pravdepodobnostiPolicok.getLukaPrav()) {
                typ = 'U';
            } else if (nahodneCislo < this->pravdepodobnostiPolicok.getLesPrav() + this->pravdepodobnostiPolicok.getLukaPrav() + this->pravdepodobnostiPolicok.getSkalaPrav()) {
                typ = 'S';
            } else {
                typ = 'V';
            }

            this->pole[r][s] = typ;
        }
    }
}

void Simulacia::nastavPolicko(int r, int s, char znak) {
    if (znak != 'L' && znak != 'U' && znak != 'S' && znak != 'V' && znak != 'P' && znak != 'Z') {
        cout << "Takyto typ policka (" << znak << ") neexistuje!" << endl;
        return;
    }
    this->pole[r][s] = znak;
}


