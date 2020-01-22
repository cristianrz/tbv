FLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 \
	-std=c11 -Wall -W -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter \
	-Wpointer-arith -Wbad-function-cast -Wno-unused-variable -Wshadow 
LIBS = -lcrypt -lbsd -lm

tvc: main.c tvc.h
	clang $(FLAGS) main.c $(LIBS) -o tvc