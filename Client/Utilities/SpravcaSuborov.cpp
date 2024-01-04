//
// Created by rucki on 4. 1. 2024.
//

#include "SpravcaSuborov.h"

string SpravcaSuborov::nacitajMapuZoSuboru(const string &nazovSuboru) {
    ifstream subor(nazovSuboru);
    if (!subor.is_open()) {
        return "";
    }

    stringstream buffer;
    buffer << subor.rdbuf();
    subor.close();

    return buffer.str();
}

bool SpravcaSuborov::ulozSimulaciuDoLokalnehoSuboru(const string& nazovSuboru, string text) {
    text = text.substr(text.find(';') + 1);

    ofstream subor(nazovSuboru);
    if (!subor.is_open()) {
        return false;
    }

    subor << text;
    subor.close();

    return true;
}
