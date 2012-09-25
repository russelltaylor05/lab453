# General test makefile for multi-target test
# General definitions

CPP = gcc
CPPFLAGS = -Wall -O3 -DLITTLE_ENDIAN -DTELL

MAIN = pipeit.o

default: pipeit
     
pipeit: $(MAIN) 
	$(CPP) $(MAIN) -o pipeit

clean: 
	rm pipeit pipeit.o

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@


# Header file interdependencies

%.c: %.h
	touch $@

