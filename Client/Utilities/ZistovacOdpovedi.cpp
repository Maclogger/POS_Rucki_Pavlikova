//
// Created by agata on 26. 12. 2023.
//

#include "ZistovacOdpovedi.h"


int ZistovacOdpovedi::vypisMenu(const string& otazka, vector<string>& moznosti) {
    cout << otazka << endl;
    for (int i = 0; i < moznosti.size(); i++) {
        cout << moznosti[i] << " - zadajte [" << i << "]" << endl;
    }

    while(true) {
        cout << "Zadajte moznost:";
        int odpoved;
        cin >> odpoved;

        if(cin.fail() || odpoved < 0 || odpoved >= moznosti.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // preskočí neplatný vstup
            cout << "Neplatny vstup, prosim, zadajte znovu. Dakujem." << endl;
            continue;
        }
        cout << odpoved << endl;
        return odpoved;
    }
}

int ZistovacOdpovedi::vypytajCislo(const string& otazka, int rozsahOd, int rozsahDo) {
    while(true) {
        cout << otazka << " <" << to_string(rozsahOd) << "; " << to_string(rozsahDo) << ">:";
        int odpoved;
        cin >> odpoved;

        if(cin.fail() || odpoved < rozsahOd || odpoved > rozsahDo) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // preskočí neplatný vstup
            cout << "Neplatny vstup, prosim, zadajte znovu. Dakujem." << endl;
            continue;
        }
        cout << odpoved << endl;
        return odpoved;
    }
}

char ZistovacOdpovedi::getZnakPolickaOdUzivatela() {
    vector<string> moznosti;
    moznosti.emplace_back("Luka");
    moznosti.emplace_back("Les");
    moznosti.emplace_back("Skala");
    moznosti.emplace_back("Voda");

    int odpoved = vypisMenu("Zvolte typ policka: ", moznosti);

    switch (odpoved) {
        case 0: return 'U';
        case 1: return 'L';
        case 2: return 'S';
    }
    return 'V';
}

string ZistovacOdpovedi::vypitajString(const string &otazka) {
    cout << otazka;
    string odpoved;
    cin >> odpoved;
    cout << odpoved << endl;
    return odpoved;
}
