//
// Created by agata on 26. 12. 2023.
//

//#ifndef CLIENT_SIMULACIA_H
//#define CLIENT_SIMULACIA_H

#include <cstdlib>
#include <iostream>
#include "PravdepodobnostiPolicok.h"
using namespace std;

class Simulacia {
private:
    int pocetRiadkov;
    int pocetStlpcov;
    char** pole;
    PravdepodobnostiPolicok pravdepodobnostiPolicok = PravdepodobnostiPolicok(25, 25, 25, 25);
public:
    Simulacia(int pocetRiadkov, int pocetStlpcov);
    void vypisSa();
    void nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav);
    ~Simulacia();

    void vygenerujSaNahodne();

    void nastavPolicko(int r, int s, char znak);
};

//
//#endif //CLIENT_SIMULACIA_H
