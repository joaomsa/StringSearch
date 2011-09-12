CC=gcc
CFLAGS=-Wall -Wextra -ansi -g -O3
EXECUTABLE=tp1

all: $(EXECUTABLE)

$(EXECUTABLE): main.o strstr.o
	$(CC) -o $@ main.o strstr.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ main.c

strstr.o: strstr.c
	$(CC) $(CFLAGS) -c -o $@ strstr.c

clean:
	rm main.o strstr.o $(EXECUTABLE)

run:
	./$(EXECUTABLE) test 5

.PHONY: clean run
