
CC = g++

CFLAGS  = -g -Wall

TARGET = day1 day2 day3 day4 day5 day6 day7 day8 day9 day10

all: $(TARGET)

day10: day10.o readInput.o
	$(CC) $(CFLAGS) -o day10 day10.o readInput.o

day10.o: day10.cpp readInput.h
	$(CC) $(CFLAGS) -c day10.cpp

day9: day9.o readInput.o
	$(CC) $(CFLAGS) -o day9 day9.o readInput.o

day9.o: day9.cpp readInput.h
	$(CC) $(CFLAGS) -c day9.cpp

day8: day8.o readInput.o
	$(CC) $(CFLAGS) -o day8 day8.o readInput.o

day8.o: day8.cpp readInput.h
	$(CC) $(CFLAGS) -c day8.cpp

day7: day7.o readInput.o
	$(CC) $(CFLAGS) -o day7 day7.o readInput.o

day7.o: day7.cpp readInput.h
	$(CC) $(CFLAGS) -c day7.cpp

day6: day6.o readInput.o
	$(CC) $(CFLAGS) -o day6 day6.o readInput.o

day6.o: day6.cpp readInput.h
	$(CC) $(CFLAGS) -c day6.cpp

day5: day5.o readInput.o
	$(CC) $(CFLAGS) -o day5 day5.o readInput.o

day5.o: day5.cpp readInput.h
	$(CC) $(CFLAGS) -c day5.cpp

day4: day4.o readInput.o
	$(CC) $(CFLAGS) -o day4 day4.o readInput.o

day4.o: day4.cpp readInput.h
	$(CC) $(CFLAGS) -c day4.cpp

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