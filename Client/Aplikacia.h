//
// Created by rucki on 29. 12. 2023.
//

#ifndef CLIENT_APLIKACIA_H
#define CLIENT_APLIKACIA_H


#include "PosSockets/my_socket.h"
#include "Logika/ZistovacOdpovedi.h"
#include "Logika/Simulacia.h"

#include <iostream>
#include <vector>
#include <string>

class Aplikacia {
private:
    MySocket* clientSocket;
    Simulacia simulacia;
public:
    Aplikacia(MySocket* clientSocket);
    ~Aplikacia();
private:
    void hlavneMenu();



};


#endif //CLIENT_APLIKACIA_H
