CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = create.h copy.h move.h rename.h delete.h search.h snapshot.h list.h utils.h
OBJ = create.o copy.o move.o rename.o delete.o search.o snapshot.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^