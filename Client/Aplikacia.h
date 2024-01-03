//
// Created by rucki on 29. 12. 2023.
//

#ifndef CLIENT_APLIKACIA_H
#define CLIENT_APLIKACIA_H


#include "Utilities/ZistovacOdpovedi.h"
#include "Logika/Simulacia.h"
#include "Utilities/ServerKomunikator.h"
#include "Logika/Serializator.h"


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
    void pokracovatVUlozenejMape();
    void spustiSimulaciu();

    void vytvorSimulaciuPodlaClientaNaServeri();

    void vykonajKrok();

    void vykonajNKrokov(int n);
};


#endif //CLIENT_APLIKACIA_H
