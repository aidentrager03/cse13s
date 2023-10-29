CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm  #math library
TESTS = tests
EXEC = calc
HEADERS = mathlib.h messages.h operators.h stack.h 
OBJECTS = mathlib.o operators.o stack.o

all: $(EXEC) $(TESTS)
debug: $(EXEC) $(TESTS)

$(TESTS): $(TESTS).o $(OBJECTS)
	$(CC) $^ $(LFLAGS) -o $@
$(EXEC): $(EXEC).o $(OBJECTS)
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(TESTS) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
