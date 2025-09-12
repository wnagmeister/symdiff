CC=gcc
CFLAGS=-Wall -Wextra

main: main.c tree.c symbols.c ast.c tokens.c 
	$(CC) -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow main.c tree.c symbols.c ast.c tokens.c void_darray.c -o main

# -fsanitize=address
