CC = gcc

CFLAGS =  -Wall\
          -Iinclude\

SOURCES = src/cAPA102.c

example = cAPA102_example

all: $(example)

$(example): example/example.c $(SOURCES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm $(example)