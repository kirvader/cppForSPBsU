#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"

int int_comp(const void *value1, const void *value2) {
	return *(int *)value1 - *(int *)value2;
}
int char_comp(const void *value1, const void *value2) {
	return *(char *)value1 - *(char *)value2;
}
int str_comp(const void *value1, const void *value2) {
	return strcmp(*(char **)value1, *(char **)value2);
}

int main(int argc, char *argv[]) {
	char *array_type = argv[1];
	char **array_source = argv + 2;
	int array_size = argc - 2;
	if (array_size < 1) {
		return 0;
	}
	if (strcmp(array_type, "int") == 0) {
		// fill
		int *int_array = malloc(array_size * sizeof(int));
		if (!int_array) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (int index = 0; index < array_size; index++)
			int_array[index] = atoi(array_source[index]);
		
		// sort
		int result_code = mergesort(int_array, array_size, sizeof(int), int_comp);
		if (result_code == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
        
		// print
		printf("%d", int_array[0]);
		for (int index = 1; index < array_size; index++) {
			printf(" %d", int_array[index]);
		}
		printf("\n");
		free(int_array);
	} else if (strcmp(array_type, "char") == 0) {
		// fill
		char *char_array = malloc(array_size * sizeof(char));
		if (!char_array) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (int index = 0; index < array_size; index++)
			char_array[index] = *array_source[index];

		// sort
		int result_code = mergesort(char_array, array_size, sizeof(char), char_comp);
		if (result_code == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}

		// print
		printf("%c", char_array[0]);
		for (int index = 1; index < array_size; index++) {
			printf(" %c", char_array[index]);
		}
		printf("\n");
		free(char_array);
	} else if (strcmp(array_type, "str") == 0) {
		// fill
		char **string_array = malloc(array_size * sizeof(char **));
		if (!string_array) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		for (int index = 0; index < array_size; index++)
		string_array[index] = array_source[index];
        
		// sort
		int result_code = mergesort(string_array, array_size, sizeof(char *), str_comp);
		if (result_code == -1) {
			printf("Error: memory allocation failed.");
			return -1;
		}
		
		// print
		printf("%s", string_array[0]);
		for (int index = 1; index < array_size; index++) {
			printf(" %s", string_array[index]);
		}
		printf("\n");
		free(string_array);
	} else {
		printf("Wrong array type!");
		return 1;
	}
	return 0;
}
