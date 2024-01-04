//
// Created by rucki on 4. 1. 2024.
//

#ifndef CLIENT_SPRAVCASUBOROV_H
#define CLIENT_SPRAVCASUBOROV_H


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

class SpravcaSuborov {


public:
    static string nacitajMapuZoSuboru(const string &nazovSuboru);

    static bool ulozSimulaciuDoLokalnehoSuboru(const string& nazovSuboru, string text);
};


#endif //CLIENT_SPRAVCASUBOROV_H
