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
    cout << "\n\n      Simulacia POZIAR\n";
    cout << "          Vytvoril:\n";
    cout << "Agata Pavlikova & Marek Rucki\n\n";

    vector<string> moznosti;
    moznosti.emplace_back("Vytvor novu simulaciu");
    moznosti.emplace_back("Pokracovat v ulozenej");
    moznosti.emplace_back("Ukoncenie");
    int odpoved = ZistovacOdpovedi().vypisMenu("Vyber jednu moznost", moznosti);

    if(odpoved == 0) {
        moznosti.clear();
        int r = ZistovacOdpovedi().vypytajCislo("Zadajte pocet riadkov mapy: ", 3, 10);
        int s = ZistovacOdpovedi().vypytajCislo("Zadajte pocet stlpcov mapy: ", 3, 10);
        this->simulacia = new Simulacia(r, s); // vytvorenie simulácie je priamo v konštruktore Simulácie
        this->spustiSimulaciu();
    } else if (odpoved == 1) {
        pokracovatVUlozenejMape();
    } else if (odpoved == 2) {
        cout << endl << "Prebieha ukoncenie. Dovidenia :)" << endl;
        return;
    }
}

void Aplikacia::pokracovatVUlozenejMape() {
    cout << "Vase predosle hry:\n";
    // TODO spravit komunikaciu so serverom a poskytnutie informacii o uložených simuláciach.
}

void Aplikacia::spustiSimulaciu() {
    //"vytvorMapu;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"
    string odpoved = this->serverKomunikator->posliSpravu("vytvorMapu;" + this->simulacia->getSerializovanuMapu());

    //"0;0;B;3;3;L;S;L;V;S;U;U;V;V;"

    cout << "odpoved zo servera: '" << odpoved << "'" << endl;


    istringstream iss(data);
    string segment;
    getline(iss, segment, ';');

    if (segment == "0") {
        // Spracovanie stringu pri status 0
        while (getline(iss, segment, ';')) {
            if (!segment.empty()) {
                if (isdigit(segment[0])) {
                    int number = stoi(segment);
                    cout << "Number: " << number << endl;
                } else {
                    cout << "Character: " << segment << endl;
                }
            }
        }
    } else if (segment == "1") {
        // Spracovanie chyby
        getline(iss, segment);  // Prečítanie zvyšku stringu
        cout << "Error: " << segment << endl;
    }



    /*odpoved = this->serverKomunikator->posliSpravu("AHOJKY");
    cout << "odpoved zo servera: '" << odpoved << "'" << endl;*/
}

