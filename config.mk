CC = clang
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 \
	-std=c11 -Wall -W -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter \
	-Wpointer-arith -Wbad-function-cast -Wno-unused-variable -Wshadow 
PREFIX = /usr/local
VERSION = v0.0.1