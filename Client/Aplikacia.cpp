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
    if (this->serverKomunikator) {
        delete this->serverKomunikator; // Uvoľnenie ServerKomunikatora
    }
    if (this->simulacia) {
        delete this->simulacia; // Uvoľnenie Simulacie, ak je ne-null
    }
}

void Aplikacia::hlavneMenu() {
    cout << "\n\n      Simulacia POZIAR\n";
    cout << "          Vytvoril:\n";
    cout << "Agata Pavlikova & Marek Rucki\n\n";

    vector<string> moznosti;
    moznosti.emplace_back("Vytvor novu simulaciu");
    moznosti.emplace_back("Vybrat simulaciu zo savov");
    moznosti.emplace_back("Ukoncenie");
    int odpoved = ZistovacOdpovedi::vypisMenu("Vyber jednu moznost:", moznosti);

    if(odpoved == 0) {
        moznosti.clear();
        int r = ZistovacOdpovedi::vypytajCislo("Zadajte pocet riadkov mapy: ", 3, 100);
        int s = ZistovacOdpovedi::vypytajCislo("Zadajte pocet stlpcov mapy: ", 3, 100);
        this->simulacia = new Simulacia(r, s); // vytvorenie simulácie je priamo v konštruktore Simulácie
        this->vytvorSimulaciuPodlaClientaNaServeri();
    } else if (odpoved == 1) {
        pokracovatVUlozenejMape();
    } else if (odpoved == 2) {
        cout << endl << "Prebieha ukoncenie. Dovidenia :)" << endl;
        return;
    }
}

void Aplikacia::pokracovatVUlozenejMape() {


    string odpovedZoServera = this->serverKomunikator->posliSpravu("ziskajUlozeneMapy;");
    vector<string> moznosti = Serializator::deserializujZoznamSavov(odpovedZoServera);

    if (moznosti.empty()) {
        cout << "Bohuzial, na serveri nie su ulozene ziadne ulozene simulacie. :(" << endl;
        return;
    }
    int indexOpdovede = ZistovacOdpovedi::vypisMenu("Ktory nacitany save chcete?", moznosti);


    string sprava = "nacitajUlozenuMapu;" + moznosti[indexOpdovede] + ";";
    odpovedZoServera = this->serverKomunikator->posliSpravu(sprava);

    this->simulacia = new Simulacia(odpovedZoServera);

    this->spustiSimulaciu();
}

void Aplikacia::vytvorSimulaciuPodlaClientaNaServeri() {
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
            string nazovNaUlozenie = ZistovacOdpovedi::vypitajString("Zadajte nazov pre ulozenie: ");
            string prikaz = "ulozMapu;" + nazovNaUlozenie + ";";
            string odpovedZoServera = this->serverKomunikator->posliSpravu(prikaz);
            if (Serializator::jeSpravaOk(odpovedZoServera)) {
                cout << "Simulacia bola uspesne ulozena." << endl;
            } else {
                cout << "Chyba, simulacia nebola ulozena." << endl;
            }
        } else if (odpoved == 3) {
            // vykonaj n krokov
            bool chceAnimaciu = ZistovacOdpovedi::ziskajBoolean("Chcete vypisat animaciu? ");

            int hornaHranica = chceAnimaciu ? 20 : 200;
            int n = ZistovacOdpovedi::vypytajCislo("Zadajte pocet krokov simulacie: ", 1, hornaHranica);

            if (chceAnimaciu) {
                for (int i = 0; i < n; i++) {
                    this->vykonajKrok();
                    this->simulacia->vypisSa();
                    Sleep(2000);
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



