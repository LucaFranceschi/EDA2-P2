
#ifndef ISPELL_GENERATE_CANDIDATES_H
#define ISPELL_GENERATE_CANDIDATES_H
#endif
#include "tree.h"
#define VOWELS 5

void candidates_by_substitution(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_insertion(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_swapping(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_deletion(char* word, Tree *dictionary, Tree *suggestions);
void generate_candidates(char* word, Tree *dictionary, Tree *substitutes);

char* delete_char_in_pos(char* word, int pos);
char* insert_char_in_pos(char* word, int pos, char ch);
char* swap_with_consecutive_char(char* word, int pos);
char* replace_char_by(char* word, int pos, char ch);

bool is_vowel(char ch);