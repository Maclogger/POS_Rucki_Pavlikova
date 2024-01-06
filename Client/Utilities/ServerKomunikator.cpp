//
// Created by agata on 29. 12. 2023.
//

#include "ServerKomunikator.h"

ServerKomunikator::ServerKomunikator(const string& ip, short port) {
    cout << "Prebieha pokus o pripojenie..." << endl;
    try {
        this->socket = MySocket::createConnection(ip, port);
    } catch (const std::runtime_error& e) {
        cout << "Pripojenie na server prebehlo neuspesne. :(" << endl;
        this->pripojeny = false;
        return;
    }
    cout << "Pripojenie na server prebehlo uspesne. :D" << endl;
    this->pripojeny = true;
}

ServerKomunikator::~ServerKomunikator() {
    if (this->jePripojeny()) {
        this->socket->sendEndMessage();
        delete this->socket;
    }
    this->socket = nullptr;
}

string ServerKomunikator::posliSpravu(const string &sprava) {
    cout << "posielana sprava: '" << sprava << "'" << endl;
    this->socket->sendData(sprava); // Najprv odoslať správu
    string odpovedZoServera = this->socket->receiveData();
    cout << "odpoved zo serveru: '" << odpovedZoServera << "'" << endl << endl;
    return odpovedZoServera; // Vrátiť prijatú správu späť zo servera
}

bool ServerKomunikator::jePripojeny() {
    return this->pripojeny;
}
