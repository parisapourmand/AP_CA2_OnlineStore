UNAME_S := $(shell uname -s)
CC := g++ -g -fsanitize=address -fno-omit-frame-pointer

all: store.out

store.out: onlineStore.o functions.o classes.o
	$(CC) onlineStore.o functions.o classes.o $(CCFLAGS) -o store.out


onlineStore.o: functions.hpp onlineStore.cpp
	$(CC) -c onlineStore.cpp -o onlineStore.o

functions.o: classes.hpp functions.hpp functions.cpp
	$(CC) -c functions.cpp -o functions.o

classes.o: classes.hpp classes.cpp
	$(CC) -c classes.cpp -o classes.o

.PHONY: clean
clean:
	rm -r *.o 