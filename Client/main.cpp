//
// Created by agata on 26. 12. 2023.
//
#include <iostream>
#include <vector>
#include "ZistovacOdpovedi.h"
#include <string>
#include "Simulacia.h"
#include "conio.h"
using  namespace std;

void pokracovatVUlozenejMape() {
    cout << "Vasa predosla hra:\n";
}



void clearScreen() {
    for (int i = 0; i < 2; i++) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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

        while (true) {
            simulacia.vypisSa();

            moznosti.clear();

            moznosti.emplace_back("Nahodne vygeneruj znova");
            moznosti.emplace_back("Manualne uprav konkretne policko");
            moznosti.emplace_back("Potvrdit aktualnu mapu");

            odpoved = ZistovacOdpovedi().vypisMenu("Vytvaranie mapy", moznosti);

            if (odpoved == 0) {
                cout << "Zadajte pravdepodobnosti pre typy policok." << endl;
                int lukaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 1/4: ", 0, 100);
                int lesPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost les 2/4 :", 0, 100 - lukaPrav);
                int skalaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 3/4 :", 0, 100 - lukaPrav - lesPrav);
                int vodaPrav = 100 - lukaPrav - lesPrav - skalaPrav;
                simulacia.nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav);
                simulacia.vygenerujSaNahodne();
                clearScreen();
                cout << "Vase zvolene pravdepodobnosti su: " << endl;
                cout << "Luka - " << to_string(lukaPrav) << "%" << endl;
                cout << "Les - " << to_string(lesPrav) << "%" << endl;
                cout << "Skala - " << to_string(skalaPrav) << "%" << endl;
                cout << "Voda - " << to_string(vodaPrav) << "%" << endl;
            } else if (odpoved == 1) {
                int rPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj riadok policka: ", 0, r - 1);
                int sPolicka = ZistovacOdpovedi().vypytajCislo("Zadaj stlpec policka: ", 0, s - 1);
                moznosti.clear();
                moznosti.emplace_back("Luka");
                moznosti.emplace_back("Les");
                moznosti.emplace_back("Skala");
                moznosti.emplace_back("Voda");

                odpoved = ZistovacOdpovedi().vypisMenu("Aky typ bude dane policko? ", moznosti);

                char znak;
                switch(odpoved) {
                    case 0: {
                        znak = 'U';
                        break;
                    }
                    case 1: {
                        znak = 'L';
                        break;
                    }
                    case 2: {
                        znak = 'S';
                        break;
                    }
                        default: {
                        znak = 'V';
                    }
                }

                simulacia.nastavPolicko(rPolicka, sPolicka, znak);



            } else {
                break;
            }
        }

    }



    return 0;
}
