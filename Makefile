
CC = g++

CFLAGS  = -g -Wall

TARGET = day1 day2

all: $(TARGET)

day2: day2.o readInput.o
	$(CC) $(CFLAGS) -o day2 day2.o readInput.o

day2.o: day2.cpp readInput.h
	$(CC) $(CFLAGS) -c day2.cpp

day1: day1.o readInput.o
	$(CC) $(CFLAGS) -o day1 day1.o readInput.o

day1.o: day1.cpp readInput.h
	$(CC) $(CFLAGS) -c day1.cpp

readInput.o: readInput.cpp readInput.h
	$(CC) $(CFLAGS) -c readInput.cpp

clean:
	rm -f $(TARGET) readInput.o