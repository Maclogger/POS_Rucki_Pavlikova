cmake_minimum_required(VERSION 3.18)
project(Client CXX)




add_executable(Client main.cpp Utilities/ZistovacOdpovedi.cpp
        Logika/Simulacia.cpp
        Logika/PravdepodobnostiPolicok.cpp
        PosSockets/my_socket.cpp
        Aplikacia.cpp
        Aplikacia.h
        Utilities/ServerKomunikator.cpp
        Utilities/ServerKomunikator.h
        Logika/Serializator.cpp
        Logika/Serializator.h
        Utilities/SpravcaSuborov.cpp
        Utilities/SpravcaSuborov.h
        Utilities/Farby.h
)

# Linkujte s Winsock knižnicou
target_link_libraries(Client wsock32 ws2_32)

