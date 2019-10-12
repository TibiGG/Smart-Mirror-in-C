CC=gcc
CFLAGS=-g -Wall -Werror -std=c99 -pedantic
LDLIBS=-lSOIL -lGL -lGLU -lglut -lm -lX11 -lpthread -lcurl
TARGET=mirror
WIDGETS=calendar clock note weather

all: $(TARGET)

$(TARGET): $(TARGET).o util.o $(foreach WIDGET, $(WIDGETS), widgets/$(WIDGET).o) widgets/jsmn.o

%.o: %.c %.h

clean:
	rm -f **/*.o *.o $(TARGET)

.PHONY: all clean
