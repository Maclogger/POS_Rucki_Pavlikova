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

    static string vypytajString(const string& otazka);

    static bool ziskajBoolean(const string& otazka);

    static int vypisMenuSBackom(const string &otazka, const vector<string>& moznosti);
};


#endif //SERVER_ZISTOVACODPOVEDI_H
