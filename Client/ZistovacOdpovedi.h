//
// Created by agata on 26. 12. 2023.
//

//#ifndef SERVER_ZISTOVACODPOVEDI_H
//#define SERVER_ZISTOVACODPOVEDI_H
#include <string>
#include <vector>
#include <iostream>
#include <limits>
using namespace  std;

class ZistovacOdpovedi {
public:
    int vypisMenu(string otazka, vector<string> moznosti  );
    int vypytajCislo(string otazka, int rozsahOd, int rozsahDo);
};


//#endif //SERVER_ZISTOVACODPOVEDI_H
