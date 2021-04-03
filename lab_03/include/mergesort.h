#ifndef LAB_03_INCLUDE_MERGESORT_H
#define LAB_03_INCLUDE_MERGESORT_H

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*));

#endif
