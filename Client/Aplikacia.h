//
// Created by rucki on 29. 12. 2023.
//

#ifndef CLIENT_APLIKACIA_H
#define CLIENT_APLIKACIA_H


#include "Utilities/ZistovacOdpovedi.h"
#include "Logika/Simulacia.h"
#include "Utilities/ServerKomunikator.h"
#include "Logika/Serializator.h"
#include "Utilities/SpravcaSuborov.h"


#include <iostream>
#include <vector>
#include <string>

class Aplikacia {
private:
    ServerKomunikator* serverKomunikator = nullptr;
    Simulacia* simulacia = nullptr;
public:
    Aplikacia(const string& ip, short port);
    ~Aplikacia();
private:
    void hlavneMenu();
    void pokracovatVUlozenejMape(const string& nazovSavu);
    void spustiSimulaciu();

    void vytvorNovuSimulaciuNaServeriPodlaFrontEndu();

    void vykonajKrok();

    void vykonajNKrokov(int n);

    string getNazovSavu();

    void zmazatSave(const string &nazovSavu);
};


#endif //CLIENT_APLIKACIA_H
