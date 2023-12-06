CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
EXECBIN = huff dehuff pqtest modetest bwtest brtest
OBJS = bitreader.o bitwriter.o node.o pc.o pqtest.o nodetest.o bwtest.o brtest.o

.PHONY: all clean format

all: $(EXECBIN)

xd: xd.o
	$(CC) $(LDFLAGS) -o $@ $^

bad_xd: bad_xd.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i -style=file *.[ch]
