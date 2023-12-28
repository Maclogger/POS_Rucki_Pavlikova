#include <stdio.h>
#include <time.h>
#include "Logika/bunka.c"
#include "Logika/simulacia.c"

#include "PosSockets/active_socket.h"
#include "PosSockets/passive_socket.h"
#include "PosSockets/char_buffer.h"

typedef struct thread_data {
    short port;
    ACTIVE_SOCKET* my_socket;
    _Bool jeKoniecKomunikacie;
};

void thread_data_init(struct thread_data* data, ACTIVE_SOCKET* sock, short port) {
    data->my_socket = sock;
    data->port = port;
    data->jeKoniecKomunikacie = false;
}

void thread_data_destroy(struct thread_data* data) {
    data->port = 0;
    data->my_socket = NULL;
}

void skus_ziskat_spravu(struct thread_data* data) {
    CHAR_BUFFER buf;
    char_buffer_init(&buf);
    if (active_socket_try_get_read_data(data->my_socket, &buf)) {
        printf("%s\n", buf.data);

        CHAR_BUFFER odpoved;
        char_buffer_init(&odpoved);
        char_buffer_append(&odpoved, "Zdravim vas tiez.", 17);

        active_socket_write_data(data->my_socket, &odpoved);

        if (active_socket_is_end_message(data->my_socket, &buf)) {
            active_socket_stop_reading(data->my_socket);
            data->jeKoniecKomunikacie = true;
        }

        char_buffer_destroy(&odpoved);
    }

    char_buffer_destroy(&buf);
}





void* process_client_data(void* thread_data) {
    struct thread_data* data = (struct thread_data*)thread_data;

    PASSIVE_SOCKET sock_passive;
    passive_socket_init(&sock_passive);
    passive_socket_start_listening(&sock_passive, data->port);
    // Spustenie počúvania
    printf("Server pocuva na porte %d\n", data->port);
    passive_socket_wait_for_client(&sock_passive, data->my_socket);
    passive_socket_stop_listening(&sock_passive);
    passive_socket_destroy(&sock_passive);

    active_socket_start_reading(data->my_socket);
}


int main() {
    srand(time(NULL));

    short port = 13028;

    struct active_socket my_socket;
    struct thread_data data;
    pthread_t th_receive;

    active_socket_init(&my_socket);

    thread_data_init(&data, &my_socket, port);


    pthread_create(&th_receive, NULL, process_client_data, &data);

    while (!data.jeKoniecKomunikacie) {
        skus_ziskat_spravu(&data);
        //printf("%d / 1000\n", i);
    }


    pthread_join(th_receive, NULL);

    thread_data_destroy(&data);
    active_socket_destroy(&my_socket);

    /*SIMULACIA sim;
    simulacia_init_default(&sim);

    simulacia_vypis_sa(&sim);

    simulacia_pridaj_ohen(&sim, 0, 0);
    simulacia_pridaj_ohen(&sim, 3, 3);

    simulacia_vypis_sa(&sim);

    simulacia_destroy(&sim);*/
    return 0;
}


