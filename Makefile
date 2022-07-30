# Makefile -- build script for the compiler of bit inverting
# functions.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sat Jul 30 22:40:24 EEST 2022

targets = mktab
toclean = $(targets)

RM     ?= rm -f

mktab_objs = mktab.o
toclean += $(mktab_objs)

all: $(targets)
clean:
	$(RM) $(toclean)

mktab: $(mktab_objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $($@_objs)
