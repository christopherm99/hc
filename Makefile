CFLAGS+= -W -Wextra -Wpedantic -Werror \
         -std=c99 -O2
LIBS=    -lutil
LDFLAGS+=


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f test a.out *.core *.o

