###################
# MAKEFILE tests  #
###################

PROJECT = test

GCC = /usr/bin/g++

std = c++20

CFLAGS += -Wall -O2 -pipe -Weffc++ -flto=4 -std=$(std)

CFLAGS_GDB = -Wall -Weffc++ -O0 -ggdb #-Werror

LDFLAGS = -lmml -lmml-math
target debug   : override CFLAGS = $(CFLAGS_GDB)

DST = test1.x

SRC = $(wildcard ./src/*.cpp *.cpp )
OBJ = $(SRC:%.cpp=%.o)

.SECONDARY: $(OBJ) # Keep the object files

all: $(DST)

clean:
	rm *.o *.x

debug: $(DST)

%.o: %.cpp
	$(GCC) $(LDFLAGS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(GCC) $< $(CFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o $@
