##################################################
##		 MAKEFILE libmml-math 		##
##		 Mike Moser 			##
##################################################

PROJECT = libmml-math

GCC = /usr/bin/g++

CFLAGS		+= -Wall -O2 -fPIC -std=c++20 -Weffc++ -flto
CFLAGS_GDB	+= -Wall -fPIC -std=c++20 -O0 -ggdb -fstack-protector-strong

MLDFLAGS = -Wl,-soname,libmml-math.so -lmml

MINCLUDE += -I include -I include/mml-math

LIBRARY += -L ./

INSTALL_DIR = /usr/lib

MSRC = $(wildcard src/*.cpp)
MOBJ = $(MSRC:%.cpp=%.o)

MDST = libmml-math.a
MINST = libmml-math.so

HPP = $(wildcard include/*.hpp )

default_target : all
target debug: override CFLAGS = $(CFLAGS_GDB)
target m.all: override INCLUDE = $(MINCLUDE)

all: $(MDST)
	@echo "\e[1;32m| Only ${shell cat $(MSRC) $(MHPP)| grep TODO | wc -l} TODOs! \e[0m"

install: $(MOBJ)
	cp -ar include /usr/local/
	$(GCC) -shared -o $(INSTALL_DIR)/$(MINST) $(MOBJ) $(MLDFLAGS) $(LIBRARY)
	ldconfig

clean:
	rm -f $(MOBJ)
	rm -f lib/$(MDST)

distclean:
	rm -f $(MOBJ)
	rm -f lib/libmml-math.a
	rm -r $(INSTALL_DIR)/$(MINST)
	rm -f /usr/local/include/mml-math.hpp
	rm -rf /usr/local/include/mml-math

debug: $(MDST)

%.o: %.cpp
	$(GCC) $(DVARS) $(MINCLUDE) $(CFLAGS) -c -o $@ $<

libmml-math.so: $(MOBJ)
	$(GCC) -shared -o lib/$(MDST) $(MOBJ) $(MLDFLAGS) $(LIBRARY)

libmml-math.a: $(MOBJ)
	ar rcs lib/$(MDST) $(MOBJ)

