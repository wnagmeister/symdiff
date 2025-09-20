#include <stdlib.h>
#include "void_darray.h"

/* void print_darray (const Darray *darray) { */
/* 	for (int i = 0; i < size(darray); i++) { */
/* 		print_valu(darray -> data[i]); */
/* 	} */
/* } */

int in_darray (void *value, const Darray *darray) {
	for (int i = 0; i < size(darray); i++) {
		if (value == darray -> data[i]) {
			return 1;
		}
	}
	return 0;
}

void *get_value (int index, const Darray *darray) {
	if (index < size(darray)) {
		return darray -> data[index];
	} else {
		return NULL;
	}
}

int capacity (const Darray *darray) {
	return darray -> cap;
}

int size (const Darray *darray) {
	return darray -> len;
}

int is_full (const Darray *darray) {
	return (darray -> len >= darray -> cap) ? 1 : 0;
}

int cap_ratio (const Darray *darray) {
	return (darray -> len * 100) / darray -> cap;
}

void o_write (void *value, int index, Darray *darray) {
	darray -> data[index] = value;
}

/* copies index+1, index+2, ... to index, index+1, ... */
static void shift_down (int index, Darray *darray) {
	for (int i = index; i < size(darray) - 1; i++) {
		darray -> data[i] = darray -> data[i+1];
	}
	darray -> len--;
}
/* copies index, index+1, ... to index+1, index+2, ... */
static void shift_up (int index, Darray *darray) {
	void *temp;
	for (int i = index; i < size(darray) - 1; i++) {
		temp = darray -> data[i];
		darray -> data[i+1] = temp;
	}
	darray -> len++;
}

int d_insert (void *value, int index, Darray *darray) {
	if (is_full (darray) || index > size(darray)) {
		return -1;
	} else {
		shift_up(index, darray);
		darray -> data[index] = value;
		return 0;
	}
}

int d_append (void *value, Darray *darray) {
	return d_insert (value, size(darray), darray);
}

void *popp (Darray *darray) {
	return del_index(size(darray) - 1 ,darray);
}

void *del_index (int index, Darray *darray) {
	if (0 <= index && index < size(darray)) {
		void *value = darray -> data[index];
		shift_down (index, darray);
		return value;
	} else {
		return NULL;
	}
}

Darray *init (int cap) {
	Darray *p = malloc(sizeof(*p));
	p -> cap = cap;
	p -> len = 0;
	p -> data = malloc(cap * sizeof(void *));
	return p;
}

int resize (int new_cap, Darray *darray) {
	if (is_full(darray)) {
		darray -> data = realloc(darray -> data, new_cap * sizeof(void *));
		darray -> cap = new_cap;
		return 0;
	} else {
		return 1;
	}
}

int f_resize (int factor, Darray *darray) {
	if (is_full(darray)) {
		darray -> data = realloc(darray -> data, factor * capacity(darray) * sizeof(void *));
		darray -> cap *= factor;
		return 0;
	} else {
		return 1;
	}
}

void destroy (Darray *darray) {
	free(darray -> data);
	free(darray);
}

// not actuallty deep destroy, not destroying deep enough
// doesnt work, increments data until its NULL
// find way to do it so struct are not changed until end
void deep_destroy (Darray *darray) {
	/*
	for (int i = 0; i < size(darray); i++) {
		free(darray -> data[i]);
	}
	*/
	while (darray -> len--) {
		free(*(darray -> data++));
	}
	free (darray);
}

void append (void *value, Darray *darray) {
	f_resize(2, darray);
	d_append(value, darray);
}

void insert (void *value, int index, Darray *darray) {
	f_resize(2, darray);
	d_insert(value, index, darray);
}
