#include "test_str.h"
#include <stdio.h>


int main() {
	test_init();
	test_my_strcpy_copy_less();
	test_my_strcpy_copy_more();
	test_my_strcat_add_less();
	test_my_strcat_add_more();
	test_my_strcmp_false_same_length();
	test_my_strcmp_false_diff_length();
	test_my_strcmp_true();
	test_my_strlen_letters();
	test_my_strlen_numbers();
	test_my_strlen_more();
	printf("All 10 tests have passed!\n");
	return 0;
}


