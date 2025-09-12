/* Dynamic array implementation with void pointers
 * no allocation checking
 * can only directly hold pointer types
 * automatically enlarges dynamic arrays if required, does not shrink
 * them*/

#ifndef VOID_DARRAY_H

#define VOID_DARRAY_H

struct Darray {
	int cap;			/* max current capacity */
	int len;			/* current size, also index of next free position */
	void **data;		/* pointer to array of void pointers */
};
typedef struct Darray Darray;

/* access functions */

/* user implemented value printing function */
/* void print_valu (void *value); */
/* void print_darray (const Darray *darray); */
int in_darray (void *value, const Darray *darray);
void *get_value (int index, const Darray *darray);

int capacity (const Darray *darray);
int size (const Darray *darray);
int is_full (const Darray *darray);
/* returns (size * 100) / capacity */
int cap_ratio (const Darray *darray);

/* functions which write elements to a specified index, possibly
 * overwriting the existing element */

void o_write (void *value, int index, Darray *darray);

/* functions which add elements */

/* "dumb" functions which no not modify the capacity
 * returns a boolean depending on success or failure */
int d_append (void *value, Darray *darray);
/* inserts value at the specified index, shifting succeeding elements */
int d_insert (void *value, int index, Darray *darray);

/* "smart" functions which resizing the darray if required */
void append (void *value, Darray *darray);
void insert (void *value, int index, Darray *darray);

/* element removal functions */

void *popp (Darray *darray);
/* deletes, returns, and shifts to cover deleted index */
void *del_index (int index, Darray *darray);

/* constructors */

Darray *init (int cap);

/* resizers */

int resize (int new_cap, Darray *darray);
int f_resize (int factor, Darray *darray);

/* destructors */

void destroy (Darray *darray);
void deep_destroy (Darray *darray);

/* macro renames for stack use */

#ifdef USE_STACK

#define Stack					Darray
#define push					append
#define peek(stack)				get_value(size(stack) - 1, stack)

#endif

/* macro renames for set use */

#ifdef USE_SET

#define Set						Darray
#define in_set					in_darray
#define is_empty(set)			(size(set) == 0)
#define add(element, set)			(in_darray(element, set) ? 1 : append(element, set), 0)

#define set_for_each(element, set)									\
	for(int i = 0, element = set -> data[i];						\
			i < size(set) ;											\
			i++, element= set -> data[i])
// define del(element, set)			del_index(get_index(element, set), set)
#define del(element, set)											\
	do {for(int i = 0; i < size(set); i++) {						\
		if (set -> data[i] == element) {del_index(i, set); break;}	\
	}} while (0)

#endif

#endif

