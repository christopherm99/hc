CFLAGS+= -W -Wextra -Wpedantic -Werror \
         -Wcast-qual -Wconversion -Wformat=2 -Wformat-security -Wnull-dereference -Wstack-protector \
         -Warray-bounds-pointer-arithmetic -Wconditional-uninitialized -Wcomma -Wpointer-arith -Widiomatic-parentheses \
         -Wunreachable-code-aggressive \
         -std=c99 -O2
LIBS=
LDFLAGS+=


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f test a.out *.core *.o

