//
// Created by agata on 26. 12. 2023.
//

#include "Simulacia.h"
#include "Serializator.h"


Simulacia::Simulacia(int pocetRiadkov, int pocetStlpcov) {
    this->pocetRiadkov  = pocetRiadkov;
    this->pocetStlpcov = pocetStlpcov;
    this->cisloKroku = 0;
    this->smerVetru = 'B';

    this->alokujPole();
    this->vygenerujSaNahodne();


    while (true) {
        this->vypisSa();

        vector<string> moznosti;
        int odpoved;
        moznosti.clear();
        moznosti.emplace_back("Nahodne vygeneruj znova");
        moznosti.emplace_back("Manualne uprav konkretne policko");
        moznosti.emplace_back("Potvrdit aktualnu mapu");
        odpoved = ZistovacOdpovedi::vypisMenu("Vytvaranie mapy", moznosti);

        cout << endl;
        if (odpoved == 0) {
            vygenerujMapuPodlaPravdepodobnostiOdUzivatela();
        } else if (odpoved == 1) {
            int rPolicka = ZistovacOdpovedi::vypytajCislo("Zadaj riadok policka: ", 0, this->pocetRiadkov - 1);
            int sPolicka = ZistovacOdpovedi::vypytajCislo("Zadaj stlpec policka: ", 0, this->pocetStlpcov - 1);
            char znak = ZistovacOdpovedi::getZnakPolickaOdUzivatela();
            this->nastavPolicko(rPolicka, sPolicka, znak);
        } else {
            break;
        }
    }
}

void Simulacia::alokujPole() {
    this->pole = static_cast<char **>(calloc(this->pocetRiadkov, sizeof(char *)));
    for (int r = 0; r < this->pocetRiadkov; r++) {
        // Alokácia stĺpcov v každom riadku
        this->pole[r] = (char*) calloc(this->pocetStlpcov, sizeof(char));
        for (int s = 0; s < this->pocetStlpcov; s++) {
            this->pole[r][s]= 'U'; // Inicializácia každej bunky
        }
    }
}

Simulacia::Simulacia(const string& serializovanyString) {
    //"0;0;B;5;5;L;S;L;V;S;U;U;V;V;S;L;V;S;S;U;L;L;U;L;L;V;U;L;L;L;"
    //"status;aktualneCisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"

    vector<string> prvky = Serializator::split(serializovanyString, ';');

    if (prvky[0] == "0") {

        this->cisloKroku = stoi(prvky[1]);
        this->smerVetru = prvky[2][0];
        this->pocetRiadkov = stoi(prvky[3]);
        this->pocetStlpcov = stoi(prvky[4]);

        this->alokujPole();

        int i = 5;
        for (int r = 0; r < pocetRiadkov; r++) {
            for (int s = 0; s < pocetStlpcov; s++) {
                this->pole[r][s]= prvky[i][0]; // Inicializácia každej bunky
                i++;
            }
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


    SetConsoleTextAttribute(hConsole, tmavoSeda);

    cout << " ";
    for (int i = 0; i < this->pocetStlpcov; i++) {
        cout << "+-----";
    }
    cout << "+";
    SetConsoleTextAttribute(hConsole, biela); // Reset na predvolenú farbu
    cout << "    -------------------------------\n";
    SetConsoleTextAttribute(hConsole, tmavoSeda);

    for (int r = 0; r < this->pocetRiadkov; r++) {
        if (r <= 9) {
            cout << " ";
        }

        SetConsoleTextAttribute(hConsole, biela); // Reset na predvolenú farbu
        cout << r << " ";
        SetConsoleTextAttribute(hConsole, tmavoSeda);
        for (int s = 0; s < this->pocetStlpcov; s++) {
            char znak = this->pole[r][s];

            cout << "|  ";

            // Nastavenie farby podľa hodnoty znaku
            switch (znak) {
                case 'U': SetConsoleTextAttribute(hConsole, zlta); break;
                case 'L': SetConsoleTextAttribute(hConsole, zelena); break;
                case 'S': SetConsoleTextAttribute(hConsole, biela); break;
                case 'V': SetConsoleTextAttribute(hConsole, modra); break;
                case 'P': SetConsoleTextAttribute(hConsole, cervena); break;
                case 'Z': SetConsoleTextAttribute(hConsole, tmavoSeda); break;
                default:  SetConsoleTextAttribute(hConsole, biela); break;
            }

            cout << znak << "  ";
            SetConsoleTextAttribute(hConsole, tmavoSeda);
        }
        cout << "|";

        char up = 'A';
        char down = 'V';
        char right = '>';
        char left = '<';

        SetConsoleTextAttribute(hConsole, biela); // Reset na predvolenú farbu

        switch(r) {
            case 0: {
                SetConsoleTextAttribute(hConsole, zlta);
                cout << "       U - luka     ";
                SetConsoleTextAttribute(hConsole, modra);
                cout << "V - voda \n";

                SetConsoleTextAttribute(hConsole, biela);
                break;
            }
            case 1: {
                SetConsoleTextAttribute(hConsole, biela);
                cout << "       S - skala    ";
                SetConsoleTextAttribute(hConsole, tmavoSeda);
                cout << "Z - zhorena\n";
                SetConsoleTextAttribute(hConsole, biela);
                break;
            }
            case 2: {
                SetConsoleTextAttribute(hConsole, cervena);
                cout << "       P - poziar   ";
                SetConsoleTextAttribute(hConsole, zelena);
                cout << "L - les  \n";
                SetConsoleTextAttribute(hConsole, biela);
                break;
            }

            case 3: {
                if (this->smerVetru == 'S') {
                    cout << "       SMER VETRU:  ";
                    SetConsoleTextAttribute(hConsole, cervena);
                    cout << up << " ";
                    SetConsoleTextAttribute(hConsole, biela);
                    cout << down << " " << left << " " << right << " X" << endl;
                }
                if (this->smerVetru == 'J') {
                    cout << "       SMER VETRU:  ";
                    cout << up << " ";
                    SetConsoleTextAttribute(hConsole, cervena);
                    cout << down << " ";
                    SetConsoleTextAttribute(hConsole, biela);
                    cout << left << " " << right << " X" << endl;
                }

                if (this->smerVetru == 'Z') {
                    cout << "       SMER VETRU:  ";
                    cout << up << " " << down << " ";
                    SetConsoleTextAttribute(hConsole, cervena);
                    cout << left << " ";
                    SetConsoleTextAttribute(hConsole, biela);
                    cout << right << " X" << endl;
                }

                if (this->smerVetru == 'V') {
                    cout << "       SMER VETRU:  ";
                    cout << up << " " << down << " " << left << " ";
                    SetConsoleTextAttribute(hConsole, cervena);
                    cout << right;
                    SetConsoleTextAttribute(hConsole, biela);
                    cout << " X" << endl;
                }

                if (this->smerVetru == 'B') {
                    cout << "       SMER VETRU:  ";
                    cout << up << " " << down << " " << left << " " << right << " ";
                    SetConsoleTextAttribute(hConsole, cervena);
                    cout << "X" << endl;
                    SetConsoleTextAttribute(hConsole, biela);
                }
                break;
            }
            case 4: {
                cout << "       Krok simulacie: ";
                SetConsoleTextAttribute(hConsole, ruzova);
                cout << to_string(this->cisloKroku) << endl;
                SetConsoleTextAttribute(hConsole, biela);
                break;
            }
            default: {
                cout << "\n";
            }

        }
        SetConsoleTextAttribute(hConsole, tmavoSeda);
        cout << "   ";

        for (int i = 0; i < this->pocetStlpcov; i++) {

            cout << "+-----";
        }
        cout << "+ \n";
    }

    // Reset farby na konci funkcie
    SetConsoleTextAttribute(hConsole, biela);
}

void Simulacia::nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav, int ohenPrav) {
    this->pravdepodobnostiPolicok.nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav, ohenPrav);
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
            } else if (nahodneCislo < this->pravdepodobnostiPolicok.getLesPrav() + this->pravdepodobnostiPolicok.getLukaPrav() + this->pravdepodobnostiPolicok.getSkalaPrav() + this->pravdepodobnostiPolicok.getVodaPrav()){
                typ = 'V';
            } else {
                typ = 'P';
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

void Simulacia::vygenerujMapuPodlaPravdepodobnostiOdUzivatela() {
    cout << "Zadajte pravdepodobnosti pre typy policok." << endl;
    int lukaPrav = ZistovacOdpovedi::vypytajCislo("Zadajte pravdepodobnost luky 1/5: ", 0, 100);
    int lesPrav = ZistovacOdpovedi::vypytajCislo("Zadajte pravdepodobnost les 2/5 :", 0, 100 - lukaPrav);
    int skalaPrav = ZistovacOdpovedi::vypytajCislo("Zadajte pravdepodobnost skaly 3/5 :", 0, 100 - lukaPrav - lesPrav);
    int vodaPrav = ZistovacOdpovedi::vypytajCislo("Zadajte pravdepodobnost vody 4/5 :", 0, 100 - lukaPrav - lesPrav - skalaPrav);
    int ohenPrav = 100 - lukaPrav - lesPrav - skalaPrav - vodaPrav;
    this->nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav, ohenPrav);
    this->vygenerujSaNahodne();
    cout << "Vase zvolene pravdepodobnosti su: " << endl;
    cout << "Luka - " << to_string(lukaPrav) << "%" << endl;
    cout << "Les - " << to_string(lesPrav) << "%" << endl;
    cout << "Skala - " << to_string(skalaPrav) << "%" << endl;
    cout << "Voda - " << to_string(vodaPrav) << "%" << endl;
    cout << "Poziar - " << to_string(ohenPrav) << "%" << endl;
}

int Simulacia::getPocetRiadkov() const {
    return this->pocetRiadkov;
}

int Simulacia::getPocetStlpcov() const {
    return this->pocetStlpcov;
}

char** Simulacia::getPole() const {
    return this->pole;
}

void Simulacia::setPocetRiadkov(int pocetRiadkov) {
    this->pocetRiadkov = pocetRiadkov;
}

void Simulacia::setPocetStlpcov(int pocetStlpcov) {
    this->pocetStlpcov = pocetStlpcov;
}

void Simulacia::setCisloKroku(int cisloKroku) {
    this->cisloKroku = cisloKroku;
}

void Simulacia::setSmerVetru(char smerVetru) {
    this->smerVetru = smerVetru;
}

bool Simulacia::skusPridatOhen(int r, int s) {
    if (r < 0 || r >= this->pocetRiadkov || s < 0 || s >= this->pocetStlpcov) {
        return false;
    }
    if (this->pole[r][s] == 'S' || this->pole[r][s] == 'V' || this->pole[r][s] == 'Z') {
        return false;
    }
    this->nastavPolicko(r, s, 'P');
    return true;
}


