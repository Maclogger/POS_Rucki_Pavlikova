//
// Created by agata on 26. 12. 2023.
//

#include "ZistovacOdpovedi.h"


int ZistovacOdpovedi::vypisMenu(string otazka, vector<string> moznosti) {
    cout << otazka << ":" << endl;
    for (int i = 0; i < moznosti.size(); i++) {
        cout << moznosti[i] << " - zadajte [" << i << "]" << endl;
    }

    cout << "Zadajte moznost:";

    while(true) {
        int odpoved;
        cin >> odpoved;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // preskočí neplatný vstup
            cout << "Neplatny vstup, prosim, zadajte znovu. Dakujem." << endl;
            continue;
        }

        if (odpoved >= 0 && odpoved < moznosti.size()) {
            return odpoved;
        } else {
            cout << "Neplatne zadane cislo.";
        }
    }
}

int ZistovacOdpovedi::vypytajCislo(string otazka, int rozsahOd, int rozsahDo) {

    cout << otazka << " od " << to_string(rozsahOd) << " do " << to_string(rozsahDo)<< endl;

    while(true) {
        int odpoved;
        cin >> odpoved;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // preskočí neplatný vstup
            cout << "Neplatny vstup, prosim, zadajte znovu. Dakujem." << endl;
            continue;
        }

        if (odpoved >= rozsahOd && odpoved <= rozsahDo) {
            return odpoved;
        } else {
            cout << "Neplatne zadane cislo.";
        }
    }
}
