//
// Created by agata on 26. 12. 2023.
//

//#ifndef CLIENT_SIMULACIA_H
//#define CLIENT_SIMULACIA_H

#include <cstdlib>
#include <iostream>
using namespace std;

class Simulacia {
private:
    int pocetRiadkov;
    int pocetStlpcov;
    char** pole;
public:
    Simulacia(int pocetRiadkov, int pocetStlpcov);
    void vypisSa();

    ~Simulacia();

};

//
//#endif //CLIENT_SIMULACIA_H
