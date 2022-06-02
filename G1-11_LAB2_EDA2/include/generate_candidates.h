
#ifndef ISPELL_GENERATE_CANDIDATES_H
#define ISPELL_GENERATE_CANDIDATES_H
#endif
#include "tree.h"

void candidates_by_substitution(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_insertion(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_swapping(char* word, Tree *dictionary, Tree *suggestions);
void candidates_by_deletion(char* word, Tree *dictionary, Tree *suggestions);
void generate_candidates(char* word, Tree *dictionary, Tree *substitutes);