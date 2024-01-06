//
// Created by agata on 26. 12. 2023.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Aplikacia.h"

using  namespace std;

/*
 Názvoslovie príkazov:

 "nazovPrikazu;argument1;argument2;...;argumentN;"

 prikazy:
    0: "vytvorMapu;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "vytvorMapu;3;3;S;S;V;L;L;U;U;S;V;"
    1: "pridajOhen;riadok;stlpec;" - "pridajOhen;2;3;"
    2: "vykonajKrok;" - "vykonajKrok;"
    3: "vykonajNKrokov;n;" - "vykonajNKrokov;8;"
    4: "ziskajUlozeneMapy;" - "ziskajUlozeneMapy;"
    5: "ulozMapu;nazovUlozenejMapy;" - "ulozMapu;extremneInteligenteNazvanaUlozenaMapa;"
    6: "nacitajUlozenuMapu;nazovUlozenejMapy;" - "nacitajUlozenuMapu;extremneInteligenteNazvanaUlozenaMapa;"
    7: "odstranUlozenuMapu;nazovUlozenejMapy;" - "odstranUlozenuMapu;extremneInteligenteNazvanaUlozenaMapa;"
    8: "vytvorMapuPodlaLokalnehoSuboru;cisloKroku;smerVetru;kolkoKratFukalVietor;pocetRiadkov;pocetStlpcov;S;kolkoHorelPoziar;S;kolkoHorelPoziar;V;kolkoHorelPoziar;L;kolkoHorelPoziar;L;kolkoHorelPoziar;U;kolkoHorelPoziar;...;S;kolkoHorelPoziar;V;kolkoHorelPoziar;"
    9: "ziskajAktualnuSimulaciuDoLokalnehoSuboru;"

odpovede:
    OK status = 0
    ERROR status = 1
    "vytvorMapu" => "status;aktualneCisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "0;3;S;3;3;S;S;V;L;L;U;U;S;V;"
    chybová hláška => "status(chybový);textChyby;" - "1;Na tejto bunke nemoze byt zalozeny poziar!;"
 */

int main() {
    #ifdef _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif
    string ip = "frios2.fri.uniza.sk";
    short port = 13028;
    Aplikacia aplikacia(ip, port);
    cout << endl;
    system("pause");
    return 0;
}
