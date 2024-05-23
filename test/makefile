###################
# MAKEFILE tests  #
###################

PROJECT = test

GCC = /usr/bin/g++

std = c++20

CFLAGS += -Wall -O2 -pipe -Weffc++ -flto=4 -std=$(std)

CFLAGS_GDB = -Wall -Weffc++ -O0 -ggdb #-Werror

INCLUDE = -I../include

LIBRARY = -L../lib

LDFLAGS = -lmml -lmml-math
target debug   : override CFLAGS = $(CFLAGS_GDB)

SRC = $(wildcard *.cpp )
OBJ = $(SRC:%.cpp=%.o)
DST =  $(SRC:%.cpp=%.x)

.SECONDARY: $(OBJ) # Keep the object files

all: $(DST)

clean:
	rm *.o *.x

debug: $(DST)

%.o: %.cpp
	$(GCC) $(LIBRARY) $(LDFLAGS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(GCC) $< $(CFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o $@

test: $(DST)
	@for i in $(DST) ;\
	do\
		./$$i;\
		sleep 2;\
	done
	

