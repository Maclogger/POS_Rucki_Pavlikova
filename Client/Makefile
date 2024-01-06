# Nastavenie kompilátora
CC=cl
CFLAGS=/EHsc
LFLAGS=wsock32.lib ws2_32.lib

# Názov spustiteľného súboru
EXE=Client.exe

# Zoznam všetkých zdrojových súborov
SOURCES=main.cpp Utilities/ZistovacOdpovedi.cpp Logika/Simulacia.cpp Logika/PravdepodobnostiPolicok.cpp PosSockets/my_socket.cpp Aplikacia.cpp Utilities/ServerKomunikator.cpp Logika/Serializator.cpp Utilities/SpravcaSuborov.cpp

# Predvolené pravidlo
all: $(EXE)

# Pravidlo pre vytvorenie spustiteľného súboru
$(EXE): $(SOURCES)
	$(CC) $(CFLAGS) /Fe$(EXE) $(SOURCES) $(LFLAGS)

# Čistenie projektu
clean:
	del *.obj *.exe

# Spustenie programu
run: $(EXE)
	$(EXE)
