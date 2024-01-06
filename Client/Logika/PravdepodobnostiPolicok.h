//
// Created by rucki on 26. 12. 2023.
//

#ifndef CLIENT_PRAVDEPODOBNOSTIPOLICOK_H
#define CLIENT_PRAVDEPODOBNOSTIPOLICOK_H

#include <iostream>
#include <string>
using namespace std;

class PravdepodobnostiPolicok {
private:
    int lukaPrav;
    int lesPrav;
    int skalaPrav;
    int vodaPrav;
    int ohenPrav;
public:
    PravdepodobnostiPolicok(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav);
    void nastavPravdepodobnosti(int lukaPrav, int lesPrav, int skalaPrav, int vodaPrav, int ohenPrav);

    int getLukaPrav() const;

    int getLesPrav() const;

    int getSkalaPrav() const;

    int getVodaPrav() const;

    ~PravdepodobnostiPolicok();
};

#endif //CLIENT_PRAVDEPODOBNOSTIPOLICOK_H
