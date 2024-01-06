.PHONY: all client server clean

# Predvolené pravidlo, ktoré skompiluje oba projekty
all: client server

# Pravidlo pre kompiláciu klienta
client:
	$(MAKE) -C Client

# Pravidlo pre kompiláciu servera
server:
	$(MAKE) -C Server

# Pravidlo pre vyčistenie oboch projektov
clean:
	$(MAKE) -C Client clean
	$(MAKE) -C Server clean
