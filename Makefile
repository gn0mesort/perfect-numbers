CC := `which clang`
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g
INCS := -Iinclude

.PHONY: all
all: perfect;

.PHONY: clean
clean:
	rm perfect.o perfect

perfect.o: include/perfect.h src/perfect.c
	$(CC) $(CFLAGS) $(INCS) -c -o perfect.o src/perfect.c

perfect: perfect.o src/main.c
	$(CC) $(CFLAGS) $(INCS) -o perfect src/main.c perfect.o

