//
// Created by rucki on 29. 12. 2023.
//

#include "Simulacia.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

#ifndef CLIENT_SERIALIZATOR_H
#define CLIENT_SERIALIZATOR_H




class Serializator {

public:
    static vector<string> split(const string& str, char delim);
    static string serializujSimualicu(Simulacia* sim);
    static void deserializujOdpovedSimulacie(Simulacia* sim, const string& odpoved);
    static vector<string> deserializujZoznamSavov(const string& odpoved);

    static bool jeSpravaOk(const string& basicString);
};


#endif //CLIENT_SERIALIZATOR_H
