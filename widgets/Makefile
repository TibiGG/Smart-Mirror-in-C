CC=gcc
CFLAGS=-g -Wall -std=c99 -pedantic
LDLIBS=-lGL -lGLU -lglut -lm -lX11 -lpthread -lcurl
TARGETS=clock calendar note weather

.PHONY: all clean

all: $(TARGETS)

test%: %.o ../util.c
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $*

%: %.o ../util.o

weather.o: weather.c weather.h ../util.c jsmn.h

%.o: %.c %.h ../util.c

clean:
	rm -f *.o $(TARGETS)
