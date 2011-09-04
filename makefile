CC=gcc
CFLAGS=-O0
EXECUTABLE=tp1

all: $(EXECUTABLE)

$(EXECUTABLE): main.o
	$(CC) -o $@ main.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ main.c

clean:
	rm main.o $(EXECUTABLE)

run:
	./$(EXECUTABLE) < test

.PHONY: clean run
