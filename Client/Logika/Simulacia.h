//
// Created by agata on 26. 12. 2023.
//

#ifndef CLIENT_SIMULACIA_H
#define CLIENT_SIMULACIA_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "../Utilities/ZistovacOdpovedi.h"
#include "PravdepodobnostiPolicok.h"
#include "winsock2.h"
#include "../Utilities/Farby.h"


using namespace std;

class Simulacia {
private:
    int pocetRiadkov;
    int pocetStlpcov;
    int cisloKroku;
    char smerVetru;
    char** pole;
    PravdepodobnostiPolicok pravdepodobnostiPolicok = PravdepodobnostiPolicok(25, 25, 25, 25);
public:
    Simulacia(int pocetRiadkov, int pocetStlpcov);

    Simulacia(const string& serializovanyString);

    ~Simulacia();

    void vypisSa();

    int getPocetRiadkov() const;

    int getPocetStlpcov() const;

    char** getPole() const;

    void nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav, int i);

    void vygenerujSaNahodne();

    void nastavPolicko(int r, int s, char znak);

    void vygenerujMapuPodlaPravdepodobnostiOdUzivatela();

    void setPocetRiadkov(int pocetRiadkov);

    void setPocetStlpcov(int pocetStlpcov);

    void setCisloKroku(int cisloKroku);

    void setSmerVetru(char smerVetru);

    bool skusPridatOhen(int r, int s);
private:
    void alokujPole();
};


#endif //CLIENT_SIMULACIA_H
