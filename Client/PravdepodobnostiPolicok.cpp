//
// Created by rucki on 26. 12. 2023.
//

#include "PravdepodobnostiPolicok.h"

PravdepodobnostiPolicok::PravdepodobnostiPolicok(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav) {
    nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav);
}

PravdepodobnostiPolicok::~PravdepodobnostiPolicok() {
}

void PravdepodobnostiPolicok::nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav) {
    if (lukaPrav + lesPrav + skalaPrav + vodaPrav != 100) {
        cout << "CHYBA!!! Sucet pravdepodobnosti nie je 100 percent!" << endl;
        cout << "Pravdepodobnosti sa nastavia na 25 percent." << endl;
        this->lukaPrav = 25;
        this->lesPrav = 25;
        this->skalaPrav = 25;
        this->vodaPrav = 25;
    } else {
        this->lukaPrav = lukaPrav;
        this->lesPrav = lesPrav;
        this->skalaPrav = skalaPrav;
        this->vodaPrav = vodaPrav;
    }
}

int PravdepodobnostiPolicok::getLukaPrav() const {
    return this->lukaPrav;
}

int PravdepodobnostiPolicok::getLesPrav() const {
    return this->lesPrav;
}

int PravdepodobnostiPolicok::getSkalaPrav() const {
    return this->skalaPrav;
}

int PravdepodobnostiPolicok::getVodaPrav() const {
    return this->vodaPrav;
}

