include config.mk

LIBS = -lcrypt -lbsd -lm
OBJ = main.c tbv.h

all: tbv

tbv: $(OBJ)
	$(CC) $(CFLAGS) main.c $(LIBS) -o tbv

clean:
	rm -f tbv tbv-$(VERSION).tar.gz main

dist: clean
	mkdir -p tbv-$(VERSION)
	cp -R LICENSE Makefile config.mk $(OBJ) tbv-$(VERSION)
	tar -czf tbv-$(VERSION).tar.gz tbv-$(VERSION)
	rm -rf tbv-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f tbv $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/tbv

.PHONY: all tbv clean dist