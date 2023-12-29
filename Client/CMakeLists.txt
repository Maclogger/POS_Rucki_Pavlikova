cmake_minimum_required(VERSION 3.18)
project(Client CXX)

add_executable(Client main.cpp Logika/ZistovacOdpovedi.cpp
        Logika/Simulacia.cpp
        Logika/PravdepodobnostiPolicok.cpp
        PosSockets/my_socket.cpp
        Aplikacia.cpp
        Aplikacia.h
        Logika/ServerKomunikator.cpp
        Logika/ServerKomunikator.h
)

# Linkujte s Winsock knižnicou
target_link_libraries(Client wsock32 ws2_32)

