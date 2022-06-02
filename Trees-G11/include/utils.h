#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 60
#define MAX_PATH_LENGTH 150
#define MAX_DEFINITION_LENGTH 100
#define MAX_LENGTH MAX_WORD_LENGTH+MAX_DEFINITION_LENGTH+5



#define LOAD_DICTIONARY 1
#define FIND_A_WORD 2
#define ADD_A_NEW_WORD 3
#define DELETE_A_WORD 4
#define IN_ORDER 5
#define PRE_ORDER 6
#define POST_ORDER 7
#define CHECK_SPELLING 8
#define BENCHMARKING 9
#define EXIT 0
#define INVALID_OPTION -1

void str_to_lowercase(char* s);
char* mystrsep(char** str_ptr, char* delim);
bool scan_line(char* message, char* format, void* buffer);
bool exists(char *filepath);
void flush_input();
int read_int_option(const char* msg);
#endif /* UTILS_H */

