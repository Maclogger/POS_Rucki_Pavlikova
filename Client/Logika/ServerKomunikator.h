//
// Created by rucki on 29. 12. 2023.
//

#include "../PosSockets/my_socket.h"
#include <string>
#include <iostream>

using namespace std;
#ifndef CLIENT_SERVERKOMUNIKATOR_H
#define CLIENT_SERVERKOMUNIKATOR_H

class ServerKomunikator {
private:
    MySocket* socket;
    bool pripojeny;
public:
    ServerKomunikator(const string& ip, short port);
    ~ServerKomunikator();
    string posliSpravu(const string& sprava);

    bool jePripojeny();
};


#endif //CLIENT_SERVERKOMUNIKATOR_H
