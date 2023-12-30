#include <stdio.h>
#include <time.h>
#include "Logika/simulacia.c"

#include "PosSockets/active_socket.h"
#include "PosSockets/passive_socket.h"
#include "PosSockets/char_buffer.h"

typedef struct thread_data {
    short port;
    ACTIVE_SOCKET* my_socket;
    _Bool jeKoniecKomunikacie;
    SIMULACIA* simulacia;
};

void thread_data_init(struct thread_data* data, ACTIVE_SOCKET* sock, short port, SIMULACIA* simulacia) {
    data->my_socket = sock;
    data->port = port;
    data->jeKoniecKomunikacie = false;
    data->simulacia = simulacia;
}

void thread_data_destroy(struct thread_data* data) {
    data->port = 0;
    data->my_socket = NULL;
}




int getCisloPrikazu(CHAR_BUFFER *buf) {

    char* token = strtok(buf->data, ";");
    if (token != NULL) {
        if (strcmp(token, "vytvorMapu") == 0) {
            return 0;
        } else if (strcmp(token, "pridajOhen") == 0) {
            return 1;
        } else if (strcmp(token, "vykonajKrok") == 0) {
            return 2;
        } else if (strcmp(token, "vykonajNKrokov") == 0) {
            return 3;
        } else if (strcmp(token, "ziskajUlozeneMapy") == 0) {
            return 4;
        } else if (strcmp(token, "ulozMapu") == 0) {
            return 5;
        } else if (strcmp(token, "nacitajUlozenuMapu") == 0) {
            return 6;
        }
    }
    return -1;
}


void skus_ziskat_spravu(struct thread_data* data) {
    CHAR_BUFFER buf;
    char_buffer_init(&buf);
    if (active_socket_try_get_read_data(data->my_socket, &buf)) {
        printf("Prijate data od clienta: '%s'\n", buf.data);

        int cisloPrikazu = getCisloPrikazu(&buf);

        switch(cisloPrikazu) {
            case 0: {
                // vytvorenie novej simulacie podla spravy
                simulacia_init_podla_spravy(data->simulacia); // ono ten strtok si to prenasa sam ten string, netreba prenasat znova buffer
                simulacia_serializuj_sa(data->simulacia, &buf);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 1: {
                // pridanie ohňa
                simulacia_pridaj_ohen(data->simulacia); // ono ten strtok si to prenasa sam ten string, netreba prenasat znova buffer
                simulacia_serializuj_sa(data->simulacia, &buf);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 2: {
                // vykonanie kroku simulacie
                vykonaj_krok(data->simulacia);
                simulacia_serializuj_sa(data->simulacia, &buf);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
        }
        if (active_socket_is_end_message(data->my_socket, &buf)) {
            active_socket_stop_reading(data->my_socket);
            data->jeKoniecKomunikacie = true;
        }
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

    short port = 13029;

    struct active_socket my_socket;
    struct thread_data data;
    pthread_t th_receive;
    SIMULACIA simulacia;

    active_socket_init(&my_socket);

    thread_data_init(&data, &my_socket, port, &simulacia);

    pthread_create(&th_receive, NULL, process_client_data, &data);

    while (!data.jeKoniecKomunikacie) {
        skus_ziskat_spravu(&data);
    }

    pthread_join(th_receive, NULL);

    simulacia_destroy(&simulacia);
    thread_data_destroy(&data);
    active_socket_destroy(&my_socket);

    return 0;
}


