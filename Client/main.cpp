//
// Created by agata on 26. 12. 2023.
//
#include <iostream>
#include <vector>
#include "ZistovacOdpovedi.h"
#include <string>
using  namespace std;

int main() {
    cout << "\n      Simulacia POZIAR\n";
    cout << "          Vytvoril:\n";
    cout << "Agata Pavlikova & Marek Rucki\n\n";

    vector<string> moznosti;

    moznosti.emplace_back("Vytvor novu simulaciu");
    moznosti.emplace_back("Pokracovat v ulozenej");
    moznosti.emplace_back("Ukoncenie");

    int odpoved = ZistovacOdpovedi().vypisMenu("Vyber jednu moznost", moznosti);

    return 0;
}