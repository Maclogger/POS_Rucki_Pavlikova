cmake_minimum_required(VERSION 3.18)
project(Server C)

set(CMAKE_C_STANDARD 11)

add_executable(Server main.c
        PosSockets/passive_socket.c
        PosSockets/active_socket.c
        PosSockets/char_buffer.c)


# Pridanie knižnice pthread pre podporu viacvláknového programovania
find_package(Threads REQUIRED)
target_link_libraries(Server Threads::Threads)



