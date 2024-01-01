//
// Created by rucki on 29. 12. 2023.
//

#include "Serializator.h"

string Serializator::serializujSimualicu(Simulacia *sim) {
    // príkaz sa tu nerieši => viacvyužiteľnosť programu
    //"pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"

    string vysledok = to_string(sim->getPocetRiadkov()) + ";" + to_string(sim->getPocetStlpcov()) + ";";

    for(int r = 0; r < sim->getPocetRiadkov(); r++) {
        for(int s = 0; s < sim->getPocetStlpcov(); s++) {
            vysledok += sim->getPole()[r][s];
            vysledok += ";";
        }
    }

    return vysledok;
}

void Serializator::deserializujOdpovedSimulacie(Simulacia *sim, const string& odpoved) {
    //"0;1;2;3;4;5;6;7;8;9;0;1;2;3;"
    //"0;0;B;3;3;L;S;L;V;S;U;U;V;V;"
    //"0;0;B;5;5;L;S;L;V;S;U;U;V;V;S;L;V;S;S;U;L;L;U;L;L;V;U;L;L;L;"
    //"status;aktualneCisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;"

    vector<string> prvky = split(odpoved, ';');

    if (!prvky.empty() && prvky[0] == "0") {

        sim->setCisloKroku(stoi(prvky[1]));
        sim->setSmerVetru(prvky[2][0]);

        int pocetRiadkov = stoi(prvky[3]);
        int pocetStlpcov = stoi(prvky[4]);
        sim->setPocetRiadkov(pocetRiadkov);
        sim->setPocetStlpcov(pocetStlpcov);

        int i = 5;
        for (int r = 0; r < pocetRiadkov; r++) {
            for (int s = 0; s < pocetStlpcov; s++) {
                sim->nastavPolicko(r, s, prvky[i][0]);
                i++;
            }
        }

    } else {
        cout << "Nastala chyba pri pokuse o deserializovanie dat ('" << odpoved << "')" << endl;
    }
}

vector<string> Serializator::split(const string &str, char delim) {
    vector<string> tokens;
    string token;
    size_t start = 0, end;

    while ((end = str.find(delim, start)) != string::npos) {
        token = str.substr(start, end - start);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        start = end + 1;
    }

    // Pridanie posledného segmentu
    token = str.substr(start);
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> Serializator::deserializujZoznamSavov(const string& odpoved) {
    vector<string> zoznam;
    zoznam = split(odpoved, ';');
    if (zoznam[0] == "0") {
        zoznam.erase(zoznam.begin());
    }
    return zoznam;
}

bool Serializator::jeSpravaOk(const string& basicString) {
    vector<string> casti = split(basicString, ';');
    return (!casti.empty() && casti[0] == "0");
}
