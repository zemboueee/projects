CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDLIBS = -lSDL2_image -lm

CFLAGS += $(shell sdl2-config --cflags)
LDLIBS += $(shell sdl2-config --libs)

VPATH = src
OBJS = rush_coke.o \
	   map.o \
	   display.o \
	   entity.o \
	   game.o \
	   vector2.o \
	   input.o \
	   utils.o \
	   update.o \
       bullet.o

all: rush_coke

rush_coke: $(OBJS)

clean:
	rm -f *.o rush_coke
