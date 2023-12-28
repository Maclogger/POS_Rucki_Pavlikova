#include <stdio.h>
#include <time.h>
#include "Logika/bunka.c"
#include "Logika/simulacia.c"

#include "PosSockets/active_socket.h"
#include "PosSockets/passive_socket.h"
#include "PosSockets/char_buffer.h"



void skus_ziskat_spravu(struct active_socket* my_socket) {
    CHAR_BUFFER buf;
    if (active_socket_try_get_read_data(my_socket, &buf)) {
        printf("%s\n", buf.data);

        CHAR_BUFFER odpoved;
        char_buffer_init(&odpoved);
        char_buffer_append(&odpoved, "Odpoved", 7);

        active_socket_write_data(my_socket, &odpoved);
        if (active_socket_is_end_message(my_socket, &buf)) {
            active_socket_stop_reading(my_socket);
        }
        char_buffer_destroy(&odpoved);
    }
}



void process_client_data(ACTIVE_SOCKET* my_socket, short port) {

    PASSIVE_SOCKET sock_passive;
    passive_socket_init(&sock_passive);
    passive_socket_start_listening(&sock_passive, port);
    // Spustenie počúvania
    printf("Server pocuva na porte %d\n", port);
    passive_socket_wait_for_client(&sock_passive, my_socket);
    passive_socket_stop_listening(&sock_passive);
    passive_socket_destroy(&sock_passive);

    active_socket_start_reading(my_socket);
}



int main() {
    srand(time(NULL));

    short port = 13029;

    struct active_socket my_socket;
    active_socket_init(&my_socket);


    process_client_data(&my_socket, port);



    // komunikacia bola nadviazana, komunikacia medzi klientom - serverom:
    printf("Komunikacia bola nadviazana.\n");
    while (my_socket.is_reading) {
        skus_ziskat_spravu(&my_socket);
    }


    /*SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vypis_sa(&sim);

    simulacia_pridaj_ohen(&sim, 0, 0);
    simulacia_pridaj_ohen(&sim, 3, 3);

    simulacia_vypis_sa(&sim);

    simulacia_destroy(&sim);*/
    return 0;
}


