#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Array *init_array (int max) {
	Array *p = malloc(sizeof(*p) + max * sizeof(void *));
	p -> max = max;
	p -> size = 0;
	return p;
}

int is_full (const Array *array) {
	return (array -> size < array ->  max) ? 0 : 1;
}

int append_array (void *value, Array *array) {
	if (is_full(array)) {
		return -1;
	} else {
		array -> array[0] = value;
		return 0;
	}
}

int in_array (void *value, const Array *array) {
	for (int i = 0; i < array -> size; i++) {
		if (value == array -> array [i]) {
			return 1;
		}
	}
	return 0;
}

