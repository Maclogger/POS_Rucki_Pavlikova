//
// Created by agata on 26. 12. 2023.
//
#include <iostream>
#include <vector>
#include "ZistovacOdpovedi.h"
#include <string>
#include "Simulacia.h"
using  namespace std;

void pokracovatVUlozenejMape() {
    cout << "Vasa predosla hra:\n";
}

int main() {
    cout << "\n      Simulacia POZIAR\n";
    cout << "          Vytvoril:\n";
    cout << "Agata Pavlikova & Marek Rucki\n\n";

    vector<string> moznosti;

    moznosti.emplace_back("Vytvor novu simulaciu");
    moznosti.emplace_back("Pokracovat v ulozenej");
    moznosti.emplace_back("Ukoncenie");

    int odpoved = ZistovacOdpovedi().vypisMenu("Vyber jednu moznost", moznosti);

    if (odpoved == 2) {
        cout << "\nPrebieha ukoncenie. Dovidenia :) \n";
        return 0;
    }

    if (odpoved == 1) {
        pokracovatVUlozenejMape();
    }

    if(odpoved == 0) {

        int r = ZistovacOdpovedi().vypytajCislo("Zadajte pocet riadkov mapy: ", 3, 10);
        int s = ZistovacOdpovedi().vypytajCislo("Zadajte pocet stlpcov mapy: ", 3, 10);

        Simulacia simulacia(r, s);
        simulacia.vypisSa();
    }



    return 0;
}
