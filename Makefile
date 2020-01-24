include config.mk

CC = clang
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 \
	-std=c11 -Wall -W -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter \
	-Wpointer-arith -Wbad-function-cast -Wno-unused-variable -Wshadow 
LIBS = -lcrypt -lbsd -lm
OBJ = main.c tvc.h

all: tvc

tvc: $(OBJ)
	$(CC) $(CFLAGS) main.c $(LIBS) -o tvc

clean:
	rm -f tvc tvc-$(VERSION).tar.gz

dist: clean
	mkdir -p tvc-$(VERSION)
	cp -R LICENSE Makefile config.mk $(OBJ) tvc-$(VERSION)
	tar -czf tvc-$(VERSION).tar.gz tvc-$(VERSION)
	rm -rf tvc-$(VERSION)

.PHONY: all tvc clean dist