CC=gcc
CFLAGS= -W -Wall -Wextra -std=gnu99
GTK= `pkg-config --cflags --libs gtk+-2.0`
EXEC=apero

all: $(EXEC)

$(EXEC): interface.o
	$(CC) $(CFLAGS) -o $@ $^ $(GTK)

main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^ $(GTK)

interface.o: interface.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(GTK)

clean:
	rm -f *.o
	rm -f $(EXEC)
