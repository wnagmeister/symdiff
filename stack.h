#ifndef STACK_H

#define STACK_H

// implementation of Stack, Set ADTs with arrays

struct Array {
	int max;		// max number of elements
	int size;		// current number of elements, doubles as index of next free position in array
	void *array[];	// elements
};
typedef struct Array Array;

void print_array (Array *array);
int append_array (void *value, Array *array);
int in_array (void *value, const Array *array);
Array *init_array (int max);
int is_full (const Array *array);

#define Stack Array

#define push(value, array) append_array(value, array)

void *pop (Array *array);


#define Set Array

Set *Union (Set *set1, Set *set2);
Set *Intersection (Set *set1, Set *set2);
Set *Difference (Set *set1, Set *set2);
int is_subset (Set *set1, Set *set2);

void **iterate (Set *set);
Set *build (void *array[]);
int add (void *element, Set *set);
int remov (void *element, Set *set);

Set *map (void *(*func)(void *), Set *set);

#endif
