CC = /usr/bin/gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = -lm -lpthread
TARGETS = temperaturUmrechner findMaxOfFloats checkprime gameOfLife matrixMult chat
SRCFILES = $(addsuffix .c, $(TARGETS))
SUBDIRS = complex matrizen zahlenraten checkPrimeMultiThreaded

all: $(SRCFILES) subdirs
	$(MAKE) $(TARGETS)

clean:
	rm -f $(TARGETS)
	for d in $(SUBDIRS); do cd $$d; $(MAKE) clean; cd ..; done

subdirs: force_true
	for d in $(SUBDIRS); do cd $$d; $(MAKE); cd ..; done

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

force_true:
	true
