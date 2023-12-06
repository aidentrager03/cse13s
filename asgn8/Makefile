CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
LDFLAGS = -lm
EXECBIN = huff dehuff pqtest nodetest bwtest brtest
OBJS = bitreader.o bitwriter.o node.o pq.o pqtest.o nodetest.o bwtest.o brtest.o huff.o dehuff.o

.PHONY: all clean format

all: $(EXECBIN)

huff: huff.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

dehuff: dehuff.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

pqtest: pqtest.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

nodetest: nodetest.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

bwtest: bwtest.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

brtest: brtest.o bitreader.o bitwriter.o node.o pq.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i -style=file *.[ch]
