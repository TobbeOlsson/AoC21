
CC = g++

CFLAGS  = -g -Wall

TARGET = day1 day2 day3

all: $(TARGET)

day3: day3.o readInput.o
	$(CC) $(CFLAGS) -o day3 day3.o readInput.o

day3.o: day3.cpp readInput.h
	$(CC) $(CFLAGS) -c day3.cpp

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
	rm -f $(TARGET) *.o readInput.o