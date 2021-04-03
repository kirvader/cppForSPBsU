#include <stddef.h>
#include <stdlib.h>
#include "mergesort.h"

void copy_array(const char *from, char *to, size_t elements) {
	while (elements--) {
		*to = *from;
		to++;
		from++;
	}
}

void merge(void *left_array,
           size_t left_array_size,
           void *right_array,
           size_t right_array_size,
           size_t element_size,
           void *new_array,
           int (*comparator)(const void*, const void*)) {
           
    while (left_array_size > 0 && right_array_size > 0) {
        if (comparator(left_array, right_array) <= 0) {
            copy_array(left_array, new_array, element_size);
            left_array += element_size;
            left_array_size--;
        } else {
            copy_array(right_array, new_array, element_size);
            right_array += element_size;
            right_array_size--;
        }
        new_array += element_size;
    }
    
    // When it's over only one of left_array_size and right_array_size would be 0.
    // So:
    copy_array(left_array, new_array, left_array_size * element_size);
    copy_array(right_array, new_array, right_array_size * element_size);
}

int mergesort(void *array,
              size_t elements,
              size_t element_size,
              int (*comparator)(const void*, const void*)) {
	if (elements < 2) return 0;
	
	size_t mid_elem_index = elements / 2;
	void *left_array = array;
	size_t left_array_size = mid_elem_index;
	void *right_array = array + mid_elem_index * element_size;
	size_t right_array_size = elements - left_array_size;
	
	if (mergesort(left_array, left_array_size, element_size, comparator) == -1) return -1;
	if (mergesort(right_array, right_array_size, element_size, comparator) == -1) return -1;
	
	void *new_array = malloc(elements * element_size);
	if (!new_array) return -1;
	merge(left_array, left_array_size, right_array, right_array_size, element_size, new_array, comparator);
	
	copy_array(new_array, array, elements * element_size);
	free(new_array);
	return 0;
}
