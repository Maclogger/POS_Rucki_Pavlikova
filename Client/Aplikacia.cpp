//
// Created by rucki on 29. 12. 2023.
//

#include "Aplikacia.h"

Aplikacia::Aplikacia(MySocket *clientSocket) {
    this->clientSocket = clientSocket;
    this->simulacia = Simulacia();
}

Aplikacia::~Aplikacia() {
    free(this->clientSocket);
    this->clientSocket = nullptr;
}

void Aplikacia::hlavneMenu() {
    cout << "\n      Simulacia POZIAR\n";
    cout << "          Vytvoril:\n";
    cout << "Agata Pavlikova & Marek Rucki\n\n";

    vector<string> moznosti;
    moznosti.emplace_back("Vytvor novu simulaciu");
    moznosti.emplace_back("Pokracovat v ulozenej");
    moznosti.emplace_back("Ukoncenie");
    int odpoved = ZistovacOdpovedi().vypisMenu("Vyber jednu moznost", moznosti);

    if(odpoved == 0) {
        vytvorenieNovejSimulacie();
    } else if (odpoved == 1) {
        pokracovatVUlozenejMape();
    } else if (odpoved == 2) {
        cout << endl << "Prebieha ukoncenie. Dovidenia :)" << endl;
        return;
    }
}

