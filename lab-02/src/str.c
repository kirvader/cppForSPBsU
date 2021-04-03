#include "str.h"
#include <stdio.h>


char *my_strcpy(char *str, char *src) {
	char *temp = str;
	while(*str++ = *src++);
	return temp;
}

char *my_strcat(char *s, char *append) {
	char *point = s;
	while (*s != '\0') s++;
	while (*s++ = *append++);
	return point;
}

int my_strcmp(char *s1, char *s2) {
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int my_strlen(char *s) {
	char *beg = s;
	while (*s != '\0') {s++;}
	return s - beg;
}
