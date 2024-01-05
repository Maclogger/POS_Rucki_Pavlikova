//
// Created by rucki on 26. 12. 2023.
//
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

    void setLukaPrav(int lukaPrav);

    int getLesPrav() const;

    void setLesPrav(int lesPrav);

    int getSkalaPrav() const;

    void setSkalaPrav(int skalaPrav);

    int getVodaPrav() const;

    void setVodaPrav(int vodaPrav);

    ~PravdepodobnostiPolicok();
};


