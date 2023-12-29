//
// Created by agata on 26. 12. 2023.
//
#include <winsock2.h>
#include <ws2tcpip.h>


#include "PosSockets/my_socket.h"
#include "Aplikacia.h"


using  namespace std;


/*
 Názvoslovie príkazov:

 "nazovPrikazu;argument1;argument2;...;argumentN;"

 prikazy:
    "vytvorMapu;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "vytvorMapu;3;3;S;S;V;L;L;U;U;S;V;"
    "pridajOhen;riadok;stlpec;" - "pridajOhen;2;3;"
    "vykonajKrok;" - "vykonajKrok;"
    "vykonajNKrokov;n;" - "vykonajNKrokov;8;"
    "ulozMapu;nazovUlozenejMapy;" - "ulozMapu;extremneInteligenteNazvanaUlozenaMapa;"


odpovede:
    "vytvorMapu" => "aktualneCisloKroku;smerVetru;pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "3;S;3;3;S;S;V;L;L;U;U;S;V;"

 */


int main() {
    string ip = "frios2.fri.uniza.sk";
    short port = 13029;
    Aplikacia aplikacia(ip, port);
    return 0;
}


