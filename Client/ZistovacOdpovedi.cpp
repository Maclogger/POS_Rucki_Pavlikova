//
// Created by agata on 26. 12. 2023.
//

#include "ZistovacOdpovedi.h"


int ZistovacOdpovedi::vypisMenu(string otazka, vector<string> moznosti) {
    cout << otazka << ":" << endl;
    for (int i = 0; i < moznosti.size(); i++) {
        cout << i << ". " << moznosti[i] << endl;
    }

    cout << "Zadajte moznosť: ";

    while(true) {
        int odpoved;
        cin >> odpoved;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // preskočí neplatný vstup
            cout << "Neplatný vstup; prosím, zadajte znovu." << endl;
            continue;
        }

        if (odpoved >= 0 && odpoved < moznosti.size()) {
            return odpoved;
        }
    }
}
