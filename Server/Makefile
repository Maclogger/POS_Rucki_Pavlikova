# Názov kompilátora
CC=gcc

# Kompilačné príznaky, -pthread je potrebný pre viacvláknovú podporu
CFLAGS=-pthread

# Zdrojové súbory
SOURCES=main.c PosSockets/passive_socket.c PosSockets/active_socket.c PosSockets/char_buffer.c

# Cieľový spustiteľný súbor
TARGET=main

# Predvolené pravidlo pre make
all: $(TARGET)

# Pravidlo na vytvorenie cieľa
$(TARGET): $(SOURCES)
        $(CC) $(CFLAGS) -o $@ $^

# Pravidlo clean na vyčistenie projektu
clean:
        rm -f $(TARGET)

