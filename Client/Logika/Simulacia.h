//
// Created by agata on 26. 12. 2023.
//

//#ifndef CLIENT_SIMULACIA_H
//#define CLIENT_SIMULACIA_H

#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "PravdepodobnostiPolicok.h"
using namespace std;

class Simulacia {
private:
    int pocetRiadkov;
    int pocetStlpcov;
    char** pole;
    PravdepodobnostiPolicok pravdepodobnostiPolicok = PravdepodobnostiPolicok(25, 25, 25, 25);
public:
    Simulacia();
    Simulacia(int pocetRiadkov, int pocetStlpcov);
    ~Simulacia();
    void vypisSa();
    void nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav);
    void vygenerujSaNahodne();
    void nastavPolicko(int r, int s, char znak);
    static void vytvorenieNovejSimulacie();
};

//
//#endif //CLIENT_SIMULACIA_H
