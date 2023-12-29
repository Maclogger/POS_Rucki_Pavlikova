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


Simulacia::Simulacia() {
    vector<string> moznosti;
    int odpoved;
    int r = ZistovacOdpovedi().vypytajCislo("Zadajte pocet riadkov mapy: ", 3, 10);
    int s = ZistovacOdpovedi().vypytajCislo("Zadajte pocet stlpcov mapy: ", 3, 10);
    Simulacia simulacia(r, s);

    while (true) {
        simulacia.vypisSa();

        moznosti.clear();
        moznosti.emplace_back("Nahodne vygeneruj znova");
        moznosti.emplace_back("Manualne uprav konkretne policko");
        moznosti.emplace_back("Potvrdit aktualnu mapu");
        odpoved = ZistovacOdpovedi().vypisMenu("Vytvaranie mapy", moznosti);

        cout << endl;
        if (odpoved == 0) {
            vygenerujMapuPodlaPravdepodobnostiOdUzivatela(simulacia);
        } else if (odpoved == 1) {
            int rPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj riadok policka: ", 0, r - 1);
            int sPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj stlpec policka: ", 0, s - 1);
            char znak = ZistovacOdpovedi().getZnakPolickaOdUzivatela();
            simulacia.nastavPolicko(rPolicka, sPolicka, znak);
        } else {
            break;
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "   ";
    for (int i = 0; i < this->pocetStlpcov; i++) {

        if (i <= 9) {
            cout << "   " << i << "  ";
        } else {
            cout << "   " << i << " ";
        }
        if (i == this->pocetStlpcov - 1) {
            cout << "              VYSVETLIVKY:";
        }
    }
    cout << endl << "  ";
    cout << " ";
    for (int i = 0; i < this->pocetStlpcov; i++) {
        cout << "+-----";


    }
    cout << "+    -------------------------------\n";

    for (int r = 0; r < this->pocetRiadkov; r++) {
        if (r <= 9) {
            cout << " ";
        }
        cout << r << " ";
        for (int s = 0; s < this->pocetStlpcov; s++) {
            char znak = this->pole[r][s];

            cout << "|  ";

            // Nastavenie farby podľa hodnoty znaku
            switch (znak) {
                case 'U': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Slabo zelená
                case 'L': SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Tmavo zelená
                case 'S': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break; // Bledo žltá
                case 'V': SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break; // Tmavo modrá
                case 'P': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break; // Červená
                case 'Z': SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break; // Biela
                default:  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break; // Predvolená farba
            }

            cout << znak << "  ";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset na predvolenú farbu
        }

        cout << "|";
        char up = 24;
        char down = 25;
        char right = 26;
        char left = 27;

        char smer = 4;
        switch(r) {
            case 0:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "       U - luka     ";
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "V - voda \n";

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
            case 1:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "       S - skala    ";

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "Z - zhorena\n";

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                break;



            case 2: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "       P - poziar   ";
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "L - les  \n";

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;

            case 3:
                if (smer ==  1) {
                    cout << "       SMER VETRA:  ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << up << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << down << " " << left << " " << right << endl;
                }
                if (smer == 2) {
                    cout << "       SMER VETRA:  ";
                    cout << up << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << down << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << left << " " << right << endl;
                }

                if (smer == 3) {
                    cout << "       SMER VETRA:  ";
                    cout << up << " " << down << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << left << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cout << right << endl;
                }

                if (smer == 4) {
                    cout << "       SMER VETRA:  ";
                    cout << up << " " << down << " " << left << " ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << right << endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }

                break;

            default: cout << "\n";

        }

        cout << "   ";

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


void Simulacia::vytvorenieNovejSimulacie() {


}

