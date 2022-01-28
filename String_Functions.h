/*
 * 	Author: BIMOS C.
 * 	Date Of Refinement: 12 - 29 - 21
 * 	Comment: Added Start Parameter to find_first_of() ;; Update at -> (9:52pm) <-
 */

#ifndef _STRING_FUNCTIONS_
#define _STRING_FUNCTIONS_
#include <stdlib.h>

size_t size(char* str){
    size_t num = 0;
    for(; str[num] != '\0'; num++);
    return num;
}
void append(char str1[], char str2[]){
    int num = size(str1);
    for(int i = 0; str2[i] != '\0'; i++){
		str1[num++] = str2[i];
    }
}

void concat(char store[], char str1[], char str2[]){
    int num = 0;
    for(int i = 0; str1[i] != '\0'; i++) store[num++] = str1[i];
    for(int i = 0; str2[i] != '\0'; i++) store[num++] = str2[i];
}
int compare(char str1[], char str2[]){
	if(size(str1)!=size(str2)) return 0;  
    for(int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) if(str1[i] != str2[i]) return 0;
    return 1;
}

int ffo(char* str, size_t start, char letters[]){
	for(int i = start; str[i]!='\0';i++){
			for(int y = 0; letters[y]!='\0';y++){
					if(str[i]==letters[y]){
							return i;
					}
			}
	}
	return -1;//npos
}

int ltbs(char letter, char letters[]){
	for(int i = 0; letters[i] != '\0';i++) if(letter == letters[i]) return i;
	return 0x27;
} // Not how you should code :/

void rot13(char str[]){
	char letters[] = "abcdefghijklmnopqrstuvwxyz0";
	for(int i = 0; str[i] != '\0'; i++)
		str[i] = (ltbs(str[i], letters) + 13 < (size(letters)-1)) ? letters[ltbs(str[i], letters) + 13]:
		letters[(ltbs(str[i], letters) + 13) - (size(letters) - 1)];
}

void reverse(char string[]){
	char c;
	for(unsigned long i = 0; i < size(string)/2; i++){
		c = string[size(string)-(i+1)];
		string[size(string)-(i+1)] = string[i];
		string[i] = c;
	}
}

char* read(){
	//if(str) free(str); We can't use this for now! The warning is annoying.
	size_t index = 0, size = 1;
	char* buffer = (char*)malloc(size);
	for(char c; (c = getchar()) != '\n'; index++){
		if(index >= size-1) buffer = (char*)realloc(buffer, ++size);
		buffer[index] = c;
	}
	buffer[index] = '\0';
	return buffer;
}
#endif
