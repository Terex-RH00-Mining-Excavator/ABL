#ifndef _PROTOTYPES_
#define _PROTOTYPES_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_ERROR "File Naming Error."
#define INDEX_ERROR "Index Out of Bounds Error."
#define MEMORY_ERROR "Memory Error."
#define SYNTAX_ERROR "Syntax Error."
#define BYTE_ERROR "Byte Error."
#define ERROR(str){								\
		fprintf(stderr,"%s\n", str);     \
		printf("ERROR: ARRAY NOT DUMPED.\n");	\
		exit(0);								\
		}										\

typedef struct{
	char beg, end;
	size_t sz, opening, closing;
	char* contents;
}Token;

Token Collect(const char*, char, char, size_t);

void Basic_Syntax(char, char*, long*, long);

void Complex_Syntax(char, char*, char**, long*, size_t*, long*);

#endif
