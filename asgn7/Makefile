CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
EXECBIN = xd bad_xd
OBJS = xd.o bad_xd.o

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
