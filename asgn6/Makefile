CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
LDFLAGS = -lm
EXECBIN = colorb iotest
OBJS = io.o bmp.o colorb.o iotest.o

.PHONY: all clean format

all: $(EXECBIN)
    
colorb: colorb.o bmp.o io.o
	$(CC) $(LDFLAGS) -o $@ $^

iotest: iotest.o io.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i -style=file *.[ch]
