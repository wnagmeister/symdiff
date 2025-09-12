CC=gcc
CFLAGS=-Wall -Wextra

main: main.c tree.c symbols.c ast.c tokens.c 
	gcc -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -fsanitize=address main.c tree.c symbols.c ast.c tokens.c void_darray.c
