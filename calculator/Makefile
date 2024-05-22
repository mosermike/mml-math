#################################
##		 MAKEFILE calc	 		#
#################################

PROJECT = calc

GCC = /usr/bin/g++

std = c++20

# Location where the log file is saved (in general in this directory to make sure that permissions are correct)
DVARS = -Dcalc_log=\"$(PWD)/calc.log\"

CFLAGS += -Wall -O2 -pipe -Weffc++ -flto=4 -std=$(std)

CFLAGS_GDB = -Wall -Weffc++ -O0 -ggdb #-Werror

INCLUDE += -I../include 

DST = calc.x

LIBRARY = -L ../lib

LDFLAGS = -lmml-math -lmml

INSTALL_DIR = /usr/local/bin

SRC = $(wildcard *.cpp )
OBJ = $(SRC:%.cpp=%.o)

target debug   : override CFLAGS = $(CFLAGS_GDB)


all: $(DST)

clean:
	rm $(OBJ) $(DST)


install: $(OBJ)
	@echo Note that the libraries libmml and libmml-math must be installed!
	$(GCC) $(OBJ) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $(INSTALL_DIR)/$(PROJECT)

uninstall:
	rm $(OBJ) $(INSTALL_DIR)/$(PROJECT)

debug: $(DST)

%.o: %.cpp
	$(GCC) $(DVARS) $(INCLUDE) $(CFLAGS) -c -o $@ $<

%.x: $(OBJ)
	$(GCC) $(OBJ) $(CFLAGS) $(INCLUDE) $(LIBRARY) $(LDFLAGS) -o $(DST)

