

CC = gcc
CFLAGS = -c -Wall -lm
OBJ = a
all: $(OBJ)
$(OBJ): airportsimulation.o queue.o
	$(CC) airportsimulation.o queue.o $(OBJ)
airportsimulation.o: airportsimulation.c
	$(CC) $(CFLAGS) airportsimulation.c
queue.o: queue.c
	$(CC) $(CFLAGS) queue.c
exec:
	./a
clean:
	rm -rf a
	rm -rf *.exe
	rm -rf *.o 


