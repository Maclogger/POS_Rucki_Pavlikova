//
// Created by rucki on 29. 12. 2023.
//

#ifndef CLIENT_APLIKACIA_H
#define CLIENT_APLIKACIA_H


#include "Logika/ZistovacOdpovedi.h"
#include "Logika/Simulacia.h"
#include "Logika/ServerKomunikator.h"
#include "Logika/Serializator.h"


#include <iostream>
#include <vector>
#include <string>

class Aplikacia {
private:
    ServerKomunikator* serverKomunikator;
    Simulacia* simulacia;
public:
    Aplikacia(const string& ip, short port);
    ~Aplikacia();
private:
    void hlavneMenu();
    void pokracovatVUlozenejMape();
    void spustiSimulaciu();
};


#endif //CLIENT_APLIKACIA_H
