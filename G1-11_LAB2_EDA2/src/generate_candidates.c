#include "generate_candidates.h"

void candidates_by_substitution(char *word, Tree *dictionary, Tree *suggestions) {
    // YOUR CODE HERE
}


void candidates_by_insertion(char* word, Tree *d, Tree *suggestions) {
    // YOUR CODE HERE
}

void candidates_by_swapping(char *word, Tree *dictionary, Tree *suggestions) {
    // YOUR CODE HERE
}
void candidates_by_deletion(char* word, Tree *d, Tree *suggestions) {
    // YOUR CODE HERE
}

void generate_candidates(char *word, Tree *dictionary, Tree *substitutes) {
    init_tree(substitutes);
    candidates_by_substitution(word, dictionary, substitutes);
    candidates_by_insertion(word, dictionary, substitutes);
    candidates_by_swapping(word,  dictionary, substitutes);
    candidates_by_deletion(word, dictionary, substitutes);
}