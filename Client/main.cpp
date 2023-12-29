//
// Created by agata on 26. 12. 2023.
//
#include <winsock2.h>
#include <ws2tcpip.h>


#include "PosSockets/my_socket.h"
#include "Aplikacia.h"


using  namespace std;

void pokracovatVUlozenejMape() {
    cout << "Vase predosle hry:\n";
    // TODO spravit komunikaciu so serverom a poskytnutie informacii o uložených hrách
}

void vygenerujMapuPodlaPravdepodobnostiOdUzivatela(Simulacia &simulacia) {
    cout << "Zadajte pravdepodobnosti pre typy policok." << endl;
    int lukaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 1/4: ", 0, 100);
    int lesPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost les 2/4 :", 0, 100 - lukaPrav);
    int skalaPrav = ZistovacOdpovedi().vypytajCislo("Zadajte pravdepodobnost luky 3/4 :", 0, 100 - lukaPrav - lesPrav);
    int vodaPrav = 100 - lukaPrav - lesPrav - skalaPrav;
    simulacia.nastavPravdepodobnosti(lukaPrav, lesPrav, skalaPrav, vodaPrav);
    simulacia.vygenerujSaNahodne();
    cout << "Vase zvolene pravdepodobnosti su: " << endl;
    cout << "Luka - " << to_string(lukaPrav) << "%" << endl;
    cout << "Les - " << to_string(lesPrav) << "%" << endl;
    cout << "Skala - " << to_string(skalaPrav) << "%" << endl;
    cout << "Voda - " << to_string(vodaPrav) << "%" << endl;

    /*simulacia.nastavPolicko(0, 0, 'P');
    simulacia.nastavPolicko(1, 0, 'P');
    simulacia.nastavPolicko(0, 1, 'P');

    simulacia.nastavPolicko(9, 9, 'Z');
    simulacia.nastavPolicko(8, 9, 'Z');
    simulacia.nastavPolicko(8, 8, 'Z');*/


}










int main() {
    try {
        cout << "Prebieha pokus o pripojenie..." << endl;
        MySocket* clientSocket = MySocket::createConnection("frios2.fri.uniza.sk", 13028);
        if (clientSocket) {

            //Aplikacia aplikacia(&clientSocket);



            clientSocket->sendData("Zdravim vas."); // Najprv odoslať správu

            string pokracovat;
            cout << clientSocket->receiveData() << endl; // Potom prijímať dáta

            clientSocket->sendEndMessage();
            delete clientSocket;
        }
    } catch (const std::runtime_error& e) {
        cerr << "Nastala vynimka:  " << e.what() << endl;
    }
    return 0;
}


