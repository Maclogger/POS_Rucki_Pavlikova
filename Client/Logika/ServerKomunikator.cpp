//
// Created by rucki on 29. 12. 2023.
//

#include "ServerKomunikator.h"

ServerKomunikator::ServerKomunikator(const string& ip, short port) {
    cout << "Prebieha pokus o pripojenie..." << endl;
    this->socket = MySocket::createConnection(ip, port);
    if (this->socket) {
        cout << "Pripojenie na server prebehlo uspesne. :D" << endl;
        this->pripojeny = true;
    } else {
        cout << "Pripojenie na server prebehlo neuspesne. :(" << endl;
        this->pripojeny = false;
    }
}

ServerKomunikator::~ServerKomunikator() {
    this->socket->sendEndMessage();
    delete this->socket;
    this->socket = nullptr;
}

string ServerKomunikator::posliSpravu(const string &sprava) {
    this->socket->sendData(sprava); // Najprv odoslať správu
    return this->socket->receiveData(); // Vrátiť prijatú správu späť zo servera
}

bool ServerKomunikator::jePripojeny() {
    return this->pripojeny;
}
