//
// Created by agata on 26. 12. 2023.
//

#ifndef SERVER_ZISTOVACODPOVEDI_H
#define SERVER_ZISTOVACODPOVEDI_H

#include <string>
#include <vector>
#include <iostream>
#include <limits>
using namespace  std;

class ZistovacOdpovedi {
public:
    static int vypisMenu(const string& otazka, vector<string>& moznosti);
    static int vypytajCislo(const string& otazka, int rozsahOd, int rozsahDo);
    static char getZnakPolickaOdUzivatela();
    static string vypitajString(const string& otazka);
};


#endif //SERVER_ZISTOVACODPOVEDI_H
