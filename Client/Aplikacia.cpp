//
// Created by rucki on 29. 12. 2023.
//

#include "Aplikacia.h"

Aplikacia::Aplikacia(const string& ip, short port) {
    this->serverKomunikator = new ServerKomunikator(ip, port);
    if (this->serverKomunikator->jePripojeny()) {
        hlavneMenu();
    }
}

Aplikacia::~Aplikacia() {
    delete this->serverKomunikator; // Uvoľnenie ServerKomunikatora
    delete this->simulacia; // Uvoľnenie Simulacie, ak je ne-null
}

void Aplikacia::hlavneMenu() {
    while (true) {
        vypisNadpis();
        vector<string> moznosti;
        moznosti.emplace_back("Vytvor novu simulaciu");
        moznosti.emplace_back("Vybrat simulaciu zo savov ulozenych na serveri");
        moznosti.emplace_back("Vymazat simulaciu zo savov ulozenych na serveri");
        moznosti.emplace_back("Nacitat mapu z lokalneho suboru");
        moznosti.emplace_back("Ukoncenie");
        int odpoved = ZistovacOdpovedi::vypisMenu("Vyber jednu moznost:", moznosti);

        if(odpoved == 0) {
            moznosti.clear();
            int r = ZistovacOdpovedi::vypytajCislo("Zadajte pocet riadkov mapy: ", 5, 100);
            int s = ZistovacOdpovedi::vypytajCislo("Zadajte pocet stlpcov mapy: ", 5, 100);
            delete this->simulacia;
            this->simulacia = new Simulacia(r, s); // vytvorenie simulácie je priamo v konštruktore Simulácie
            this->vytvorNovuSimulaciuNaServeriPodlaFrontEndu();
        } else if (odpoved == 1) {
            string nazovSavu = this->getNazovSavu();
            if (!nazovSavu.empty()) {
                this->pokracovatVUlozenejMape(nazovSavu);
            }
        } else if (odpoved == 2) {
            string nazovSavu = this->getNazovSavu();
            if (!nazovSavu.empty()) {
                this->zmazatSave(nazovSavu);
            }
        } else if (odpoved == 3) {
            // nacitanie mapy z lokálneho súboru
            string spravaPreServer = "vytvorMapuPodlaLokalnehoSuboru;" + SpravcaSuborov::nacitajMapuZoSuboru("../lokalny.txt");
            string odpovedZoServera = this->serverKomunikator->posliSpravu(spravaPreServer);
            if (Serializator::jeSpravaOk(odpovedZoServera)) {
                cout << "Simulacia bola uspesne nacitana z lokalneho suboru." << endl;
                delete this->simulacia;
                this->simulacia = new Simulacia(odpovedZoServera);
                this->spustiSimulaciu();
            } else {
                cout << "Simulacia nebola nacitana z lokalneho suboru. Pravdepodobne zly format vstupu." << endl;
            }
        } else {
            cout << endl << "Prebieha ukoncenie. Dovidenia :)" << endl;
            return;
        }
    }
}

void Aplikacia::vypisNadpis() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n\n      Simulacia ";
    SetConsoleTextAttribute(hConsole, cervena);
    cout << "POZIAR\n";
    SetConsoleTextAttribute(hConsole, biela);
    cout << "          Vytvoril:\n";
    SetConsoleTextAttribute(hConsole, ruzova);
    cout << "Agata Pavlikova ";
    SetConsoleTextAttribute(hConsole, biela);
    cout << "& ";
    SetConsoleTextAttribute(hConsole, modra);
    cout << "Marek Rucki\n\n";
    SetConsoleTextAttribute(hConsole, biela);
}

string Aplikacia::getNazovSavu() {
    string odpovedZoServera = this->serverKomunikator->posliSpravu("ziskajUlozeneMapy;");
    vector<string> moznosti = Serializator::deserializujZoznamSavov(odpovedZoServera);

    if (moznosti.empty()) {
        cout << "Bohuzial, na serveri nie su ulozene ziadne ulozene simulacie. :(" << endl;
        return "";
    }

    int indexOpdovede = ZistovacOdpovedi::vypisMenuSBackom("Ktory save chcete?", moznosti);

    return (indexOpdovede == -1) ? "" : moznosti[indexOpdovede];
}

void Aplikacia::zmazatSave(const string &nazovSavu) {

    string sprava = "odstranUlozenuMapu;" + nazovSavu + ";";
    string odpovedZoServera = this->serverKomunikator->posliSpravu(sprava);

    if (Serializator::jeSpravaOk(odpovedZoServera)) {
        cout << "Save bol zmazany zo serveru. :D" << endl;
        return;
    }

    cout << "Save nebol zmazany zo serveru. :(" << endl;
}

void Aplikacia::pokracovatVUlozenejMape(const string& nazovSavu) {

    string sprava = "nacitajUlozenuMapu;" + nazovSavu + ";";
    string odpovedZoServera = this->serverKomunikator->posliSpravu(sprava);

    delete this->simulacia;
    this->simulacia = new Simulacia(odpovedZoServera);

    this->spustiSimulaciu();
}

void Aplikacia::vytvorNovuSimulaciuNaServeriPodlaFrontEndu() {
    //"vytvorMapu;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"
    string odpovedZoServera = this->serverKomunikator->posliSpravu("vytvorMapu;" + Serializator::serializujSimualicu(this->simulacia));
    Serializator::deserializujOdpovedSimulacie(this->simulacia, odpovedZoServera);
    this->spustiSimulaciu();
}

void Aplikacia::spustiSimulaciu() {
    while(true) {
        cout << endl << endl;
        this->simulacia->vypisSa();
        vector<string> moznosti;
        moznosti.emplace_back("Vykonat krok simulacie");
        moznosti.emplace_back("Pridat ohen");
        moznosti.emplace_back("Ulozit simulaciu na server");
        moznosti.emplace_back("Ulozit simulaciu do lokalneho subora");
        moznosti.emplace_back("Vykonat n krokov simulacie");
        moznosti.emplace_back("Ukoncit simulaciu");

        int odpoved = ZistovacOdpovedi::vypisMenu("\n", moznosti);

        if (odpoved == 0) {
            this->vykonajKrok();
        } else if (odpoved == 1) {
            int riadokNovehoOhna;
            int stlpecNovehoOhna;
            while (true) {
                riadokNovehoOhna = ZistovacOdpovedi::vypytajCislo("Zadajte riadok policka", 0, this->simulacia->getPocetRiadkov() - 1);
                stlpecNovehoOhna = ZistovacOdpovedi::vypytajCislo("Zadajte stlpec policka", 0, this->simulacia->getPocetStlpcov() - 1);
                if (this->simulacia->skusPridatOhen(riadokNovehoOhna, stlpecNovehoOhna)) break;
                cout << "Na tomto policku nemoze byt zalozeny poziar!" << endl;
            }
            // "pridajOhen;riadok;stlpec;" - "pridajOhen;2;3;"
            string prikaz = "pridajOhen;" + to_string(riadokNovehoOhna) + ";" + to_string(stlpecNovehoOhna) + ";";
            string odpovedZoServera = this->serverKomunikator->posliSpravu(prikaz);
            Serializator::deserializujOdpovedSimulacie(this->simulacia, odpovedZoServera);
        } else if (odpoved == 2) {
            string nazovNaUlozenie = ZistovacOdpovedi::vypytajString("Zadajte nazov pre ulozenie: ");
            string prikaz = "ulozMapu;" + nazovNaUlozenie + ";";
            string odpovedZoServera = this->serverKomunikator->posliSpravu(prikaz);
            if (Serializator::jeSpravaOk(odpovedZoServera)) {
                cout << "Simulacia bola uspesne ulozena." << endl;
            } else {
                cout << "Chyba, simulacia nebola ulozena." << endl;
            }
        } else if (odpoved == 3) {
            string odpovedZoServera = this->serverKomunikator->posliSpravu("ziskajAktualnuSimulaciuDoLokalnehoSuboru;");
            if (Serializator::jeSpravaOk(odpovedZoServera)) {
                if (SpravcaSuborov::ulozSimulaciuDoLokalnehoSuboru("../lokalny.txt", odpovedZoServera)) {
                    cout << "Simulacia bola uspesne ulozena do lokalneho suboru. :D" << endl;
                    continue;
                }
            }
            cout << "Simulacia nebola ulozena. Niekde sa vyskytla chyba. :(" << endl;
        } else if (odpoved == 4) {
            // vykonaj n krokov
            bool chceAnimaciu = ZistovacOdpovedi::ziskajBoolean("Chcete vypisat animaciu? ");

            int hornaHranica = chceAnimaciu ? 20 : 300;
            int n = ZistovacOdpovedi::vypytajCislo("Zadajte pocet krokov simulacie: ", 1, hornaHranica);

            if (chceAnimaciu) {
                for (int i = 0; i < n; i++) {
                    this->vykonajKrok();
                    this->simulacia->vypisSa();
                    Sleep(1500);
                }
            } else {
                this->vykonajNKrokov(n);
            }
        } else {
            break;
        }
    }
}

void Aplikacia::vykonajKrok() {
    string odpovedZoServera = this->serverKomunikator->posliSpravu("vykonajKrok;");
    Serializator::deserializujOdpovedSimulacie(this->simulacia, odpovedZoServera);
}

void Aplikacia::vykonajNKrokov(int n) {
    string odpovedZoServera = this->serverKomunikator->posliSpravu("vykonajNKrokov;" + to_string(n) + ";");
    Serializator::deserializujOdpovedSimulacie(this->simulacia, odpovedZoServera);
}






