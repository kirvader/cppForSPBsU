#include <assert.h>
#include <string.h>
#include "str.h"
#include <stddef.h>

char s1[20];
void test_init (){
	s1[0] = 'a';
	s1[1] = 'b';
	s1[2] = 'c';
	s1[3] = 'd';
	s1[4] = 'e';
	s1[5] = '\0';
}

void test_my_strcpy(char *first, char *second) {
	char *actual = my_strcpy(first, second);
	char *expected = second;
	assert(strcmp(actual, expected) == 0);
}

void test_my_strcat(char *first, char *second) {
	char *actual = my_strcat(first, second);
	char *expected = strcat(first, second);
	assert(strcmp(actual, expected) == 0);
}

void test_my_strcmp(char *first, char *second) {
	int actual = my_strcmp(first, second);
	int expected = strcmp(first, second);
	assert((expected == 0 && actual == 0) || actual * expected > 0);
}

void test_my_strlen(char *first) {
	size_t actual = my_strlen(first);
	size_t expected = strlen(first);
	assert(actual == expected);
}

void test_my_strcpy_copy_less() {
	// символов в копируемой строке больше
	test_my_strcpy(s1, "123");
}
void test_my_strcpy_copy_more() {
	// символов в копируемой строке больше
	test_my_strcpy(s1, "1234678");
}
void test_my_strcat_add_less() {
	// символов в добавляемой строке меньше
	test_my_strcat(s1, "123");
}

void test_my_strcat_add_more() {
	// символов в добавляемой строке больше
	test_my_strcat(s1, "12345678");
}

void test_my_strcmp_false_same_length() {
	// отрицательное значение
	test_my_strcmp("12345676", "12345678");
}

void test_my_strcmp_false_diff_length() {
	// символов в первой строке больше
	test_my_strcmp("123456789", "12345678");
}

void test_my_strcmp_true() {
	// одинаковые
	test_my_strcmp("123456789", "123456789");
}

void test_my_strlen_letters() {
	// 5 : буквы
	test_my_strlen("first");
}

void test_my_strlen_numbers() {
	// 7 : цифры
	test_my_strlen("1234567");
}

void test_my_strlen_more() {
	// 9 : буквы и цифры
	test_my_strlen("1234567ab");
}
