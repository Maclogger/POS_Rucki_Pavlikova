#include <stdio.h>
#include <time.h>
#include "Utilities/spravca.c"
#include "Logika/simulacia.c"

#include "PosSockets/active_socket.h"
#include "PosSockets/passive_socket.h"
#include "PosSockets/char_buffer.h"

typedef struct thread_data {
    short port;
    ACTIVE_SOCKET* my_socket;
    _Bool jeKoniecKomunikacie;
    SIMULACIA* simulacia;
} THREAD_DATA;

void thread_data_init(THREAD_DATA* data, ACTIVE_SOCKET* sock, short port, SIMULACIA* simulacia) {
    data->my_socket = sock;
    data->port = port;
    data->jeKoniecKomunikacie = false;
    data->simulacia = simulacia;
}

void thread_data_destroy(THREAD_DATA* data) {
    data->port = 0;
    data->my_socket = NULL;
}

int getCisloPrikazu(CHAR_BUFFER *buf) {
    //"pocetRiadkov;pocetStlpcov;S;S;V;L;L;U;...;S;V;" - "vytvorMapu;3;3;S;S;V;L;L;U;U;S;V;"
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
        } else if (strcmp(token, "odstranUlozenuMapu") == 0) {
            return 7;
        } else if (strcmp(token, "vytvorMapuPodlaLokalnehoSuboru") == 0) {
            return 8;
        } else if (strcmp(token, "ziskajAktualnuSimulaciuDoLokalnehoSuboru") == 0) {
            return 9;
        }
    }
    return -1;
}

void skus_ziskat_spravu(THREAD_DATA* data) {
    CHAR_BUFFER buf;
    char_buffer_init(&buf);
    char* nazovSuboruSavov = "saves.txt";

    if (active_socket_try_get_read_data(data->my_socket, &buf)) {
        printf("Prijate data od clienta: '%s'\n", buf.data);

        if (active_socket_is_end_message(data->my_socket, &buf)) {
            active_socket_stop_reading(data->my_socket);
            data->jeKoniecKomunikacie = true;
            char_buffer_destroy(&buf);
            return;
        }

        int cisloPrikazu = getCisloPrikazu(&buf);

        switch(cisloPrikazu) {
            case 0: {
                // vytvorenie novej simulacie podla spravy
                if (data->simulacia->initialized) {
                    simulacia_destroy(data->simulacia);
                }
                simulacia_init_podla_spravy_vytvorenia(data->simulacia); // ono ten strtok si to prenasa sam ten string, netreba prenasat znova buffer
                char_buffer_clear(&buf);
                simulacia_serializuj_sa(data->simulacia, &buf);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 1: {
                // pridanie ohňa
                simulacia_pridaj_ohen(data->simulacia); // ono ten strtok si to prenasa sam ten string, netreba prenasat znova buffer
                char_buffer_clear(&buf);
                simulacia_serializuj_sa(data->simulacia, &buf);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
                //priklad;0;B;5;5;L;S;L;V;S;U;U;V;V;S;L;V;S;S;U;L;L;U;L;L;V;U;L;L;L;
            }
            case 2: {
                // vykonanie kroku simulacie
                char_buffer_clear(&buf);
                simulacia_vykonaj_krok_a_serializuj_sa(data->simulacia, &buf);
                /*vykonaj_krok(data->simulacia);
                simulacia_serializuj_sa(data->simulacia, &buf);*/
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 3: {
                char* token = strtok(NULL, ";");
                int n = atoi(token);
                for (int i = 0; i < n; i++) {
                    vykonaj_krok(data->simulacia, 0);
                }
                char_buffer_clear(&buf);
                simulacia_serializuj_sa(data->simulacia, &buf);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 4: {
                // ziskajUlozeneMapy
                SPRAVCA spravca;
                spravca_init(&spravca, nazovSuboruSavov);
                char_buffer_clear(&buf);
                serializuj_nazvy_vsetkych_savov(&spravca, &buf);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                spravca_destroy(&spravca);
                break;
            }
            case 5: {
                // ulozMapu
                SPRAVCA spravca;
                spravca_init(&spravca, nazovSuboruSavov);
                char* nazovSuboru = strtok(NULL, ";");

                CHAR_BUFFER retazec;
                char_buffer_init(&retazec);
                char_buffer_append(&retazec, nazovSuboru, strlen(nazovSuboru));
                char_buffer_append(&retazec, ";", 1);

                simulacia_serializuj_sa_pre_save(data->simulacia, &retazec);
                char_buffer_append(&retazec, "\0", 1);

                if (uloz_novy_save(&spravca, retazec.data)) {
                    char_buffer_clear(&retazec);
                    char_buffer_append(&retazec, "0;\0", 3);
                } else {
                    char_buffer_clear(&retazec);
                    char_buffer_append(&retazec, "1;\0", 3);
                }

                active_socket_write_data(data->my_socket, &retazec);

                char_buffer_destroy(&retazec);
                spravca_destroy(&spravca);
                break;
            }
            case 6: {
                // nacitajUlozenuMapu
                SPRAVCA spravca;
                spravca_init(&spravca, nazovSuboruSavov);

                CHAR_BUFFER stringZoSuboru;
                char_buffer_init(&stringZoSuboru);

                get_save_zo_suboru(&spravca, strtok(NULL, ";"), &stringZoSuboru);

                // ignoracia nazvu savu:
                strtok(stringZoSuboru.data, ";");
                if (data->simulacia->initialized) {
                    simulacia_destroy(data->simulacia);
                }
                simulacia_init_podla_celkoveho_stringu(data->simulacia, &stringZoSuboru);

                char_buffer_clear(&buf);
                simulacia_serializuj_sa(data->simulacia, &buf);
                printf("Odosialene data: %s\n", buf.data);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);

                char_buffer_destroy(&stringZoSuboru);
                spravca_destroy(&spravca);
                break;
            }
            case 7: {
                // odstranUlozenuMapu
                SPRAVCA spravca;
                spravca_init(&spravca, nazovSuboruSavov);
                _Bool boloUspesne = spravca_zmaz_save(&spravca, strtok(NULL, ";"));
                spravca_destroy(&spravca);
                char_buffer_clear(&buf);
                if (boloUspesne) {
                    char_buffer_append(&buf, "0;\0", 3);
                } else {
                    char_buffer_append(&buf, "1;\0", 3);
                }
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 8: {
                // vytvorMapuPodlaLokalnehoSuboru
                if (data->simulacia->initialized) {
                    simulacia_destroy(data->simulacia);
                }
                simulacia_init_podla_celkoveho_stringu(data->simulacia, &buf);
                char_buffer_clear(&buf);
                simulacia_serializuj_sa(data->simulacia, &buf);
                printf("Odosialene data: %s\n", buf.data);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            case 9: {
                // ziskajAktualnuSimulaciuDoLokalnehoSuboru
                char_buffer_clear(&buf);
                char_buffer_append(&buf, "0;", 2);
                simulacia_serializuj_sa_pre_save(data->simulacia, &buf);
                char_buffer_append(&buf, "\0", 1);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
            default: {
                char_buffer_clear(&buf);
                char_buffer_append(&buf, "1;Tento prikaz neexistuje!\0", 27);
                active_socket_write_data(data->my_socket, &buf);
                break;
            }
        }
    }
    char_buffer_destroy(&buf);
}

void* process_client_data(void* thread_data) {
    THREAD_DATA* data = (THREAD_DATA*)thread_data;

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

    ACTIVE_SOCKET my_socket;
    THREAD_DATA data;

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


