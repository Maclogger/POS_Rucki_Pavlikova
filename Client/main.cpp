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
    cout << "Vase predosle hry:\n";
    // TODO spravit komunikaciu so serverom a poskytnutie informacii o uložených hrách
}

void vygenerujMapuPodlaPravdepodobnostiOdUzivatela(Simulacia &simulacia) {
    cout << "Zadajte pravdepodobnosti pre typy policok." << endl;
    int lukaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 1/4: ", 0, 100);
    int lesPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost les 2/4 :", 0, 100 - lukaPrav);
    int skalaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 3/4 :", 0, 100 - lukaPrav - lesPrav);
    int vodaPrav = 100 - lukaPrav - lesPrav - skalaPrav;
    simulacia.nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav);
    simulacia.vygenerujSaNahodne();
    cout << "Vase zvolene pravdepodobnosti su: " << endl;
    cout << "Luka - " << to_string(lukaPrav) << "%" << endl;
    cout << "Les - " << to_string(lesPrav) << "%" << endl;
    cout << "Skala - " << to_string(skalaPrav) << "%" << endl;
    cout << "Voda - " << to_string(vodaPrav) << "%" << endl;
}

void vytvorenieNovejSimulacie() {
    vector<string> moznosti;
    int odpoved;
    int r = ZistovacOdpovedi().vypytajCislo("Zadajte pocet riadkov mapy: ", 3, 10);
    int s = ZistovacOdpovedi().vypytajCislo("Zadajte pocet stlpcov mapy: ", 3, 10);
    Simulacia simulacia(r, s);

    while (true) {
        simulacia.vypisSa();

        moznosti.clear();
        moznosti.emplace_back("Nahodne vygeneruj znova");
        moznosti.emplace_back("Manualne uprav konkretne policko");
        moznosti.emplace_back("Potvrdit aktualnu mapu");
        odpoved = ZistovacOdpovedi().vypisMenu("Vytvaranie mapy", moznosti);

        if (odpoved == 0) {
            vygenerujMapuPodlaPravdepodobnostiOdUzivatela(simulacia);
        } else if (odpoved == 1) {
            int rPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj riadok policka: ", 0, r - 1);
            int sPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj stlpec policka: ", 0, s - 1);
            char znak = ZistovacOdpovedi().getZnakPolickaOdUzivatela();
            simulacia.nastavPolicko(rPolicka, sPolicka, znak);
        } else {
            break;
        }
    }

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

    if(odpoved == 0) {
        vytvorenieNovejSimulacie();
    } else if (odpoved == 1) {
        pokracovatVUlozenejMape();
    } else if (odpoved == 2) {
        cout << endl << "Prebieha ukoncenie. Dovidenia :)" << endl;
        return 0;
    }

    return 0;
}


