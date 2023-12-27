#include <stdio.h>
#include <time.h>
#include "Logika/bunka.c"
#include "Logika/simulacia.c"

#include "PosSockets/active_socket.h"
#include "PosSockets/passive_socket.h"
#include "PosSockets/char_buffer.h"


int main() {
    srand(time(NULL));

    // Inicializácia pasívneho soketu
    PASSIVE_SOCKET serverSocket;
    passive_socket_init(&serverSocket);

    short port = 8081;

    // Spustenie počúvania na porte 8080
    if (!passive_socket_start_listening(&serverSocket, port)) {
        fprintf(stderr, "Nepodarilo sa zacat pocuvat na porte %d\n", port);
        return 1;
    }

    printf("Server pocuva na porte %d\n", port);


    // Čakanie na klienta
    while (1) {
        ACTIVE_SOCKET clientSocket;
        if (passive_socket_wait_for_client(&serverSocket, &clientSocket)) {
            printf("Klient pripojeny\n");

            // Začatie čítania dát
            active_socket_start_reading(&clientSocket);

            // Skúste získať prijaté dáta
            struct char_buffer readBuffer;
            if (active_socket_try_get_read_data(&clientSocket, &readBuffer)) {
                // Vypíšte prijaté dáta
                printf("Prijata sprava: %s\n", readBuffer.data);
            }

            // Ukončenie čítania a spojenia s klientom
            active_socket_stop_reading(&clientSocket);
            active_socket_destroy(&clientSocket);

            break; // Prerušenie po prijatí jednej správy (pre ukončenie slučky)
        }
    }

    // Zastavenie počúvania a uvoľnenie zdrojov
    passive_socket_stop_listening(&serverSocket);
    passive_socket_destroy(&serverSocket);


    /*SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vypis_sa(&sim);

    simulacia_pridaj_ohen(&sim, 0, 0);
    simulacia_pridaj_ohen(&sim, 3, 3);

    simulacia_vypis_sa(&sim);

    simulacia_destroy(&sim);*/
    return 0;
}


