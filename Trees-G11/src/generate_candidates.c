#include "generate_candidates.h"

void candidates_by_insertion(char* word, Tree *d, Tree *suggestions) {
    for (int i = 0; i < strlen(word)+1; ++i) {
        for (int ch = 97; ch < 123; ++ch) {
            // INSERT 1 CHARACTER
            char* candidate;
            if (i == 0){
                candidate = insert_char_in_pos(word, i, (char)(ch-32));
            } else {
                candidate = insert_char_in_pos(word, i, (char)ch);
            }
            if (find_in_tree(d, candidate) != NULL && strcmp(candidate, "") != 0){
                insert_into_tree(suggestions, candidate);
            }

            // INSERT 2 CHARACTERS
            char* candidate2;
            for (int ch2 = 97; ch2 < 123; ++ch2) {
                if (i == 0){
                    candidate2 = insert_char_in_pos(candidate, i+1, (char)(ch2-32));
                } else {
                    candidate2 = insert_char_in_pos(candidate, i+1, (char)ch2);
                }
                if (find_in_tree(d, candidate2) != NULL && strcmp(candidate2, "") != 0){
                    insert_into_tree(suggestions, candidate2);
                }
            }
        }
    }
}

void candidates_by_deletion(char* word, Tree *d, Tree *suggestions) {
    for (int i = 0; i < strlen(word); ++i) {
        // DELETING ONE CHAR
        char* candidate = delete_char_in_pos(word, i);
        if (find_in_tree(d, candidate) != NULL && strcmp(candidate, "") != 0){
            insert_into_tree(suggestions, candidate);
        }

        // DELETING TWO CHARS
        char* candidate2 = delete_char_in_pos(candidate, i);
        if (find_in_tree(d, candidate2) != NULL && strcmp(candidate2, "") != 0){
            insert_into_tree(suggestions, candidate2);
        }
    }
}

void candidates_by_swapping(char *word, Tree *dictionary, Tree *suggestions) {
    for (int i = 0; i < strlen(word)-1; i++){
        char* candidate = swap_with_consecutive_char(word, i);
        if (find_in_tree(dictionary, candidate) != NULL && strcmp(candidate, "") != 0){
            insert_into_tree(suggestions, candidate);
        }
    }
}

void candidates_by_substitution(char *word, Tree *dictionary, Tree *suggestions) {
    for (int i = 0; i < strlen(word); i++){
        if (is_vowel(word[i])){
            char vowels[VOWELS] = {'a', 'e', 'i', 'o', 'u'};
            for (int j = 0; j < VOWELS; ++j) {
                char* candidate = replace_char_by(word, i, vowels[j]);
                if (find_in_tree(dictionary, candidate) != NULL && strcmp(candidate, "") != 0){
                    insert_into_tree(suggestions, candidate);
                }
            }
        }

    }
}

void generate_candidates(char *word, Tree *dictionary, Tree *substitutes) {
    init_tree(substitutes);
    candidates_by_substitution(word, dictionary, substitutes);
    candidates_by_insertion(word, dictionary, substitutes);
    candidates_by_swapping(word,  dictionary, substitutes);
    candidates_by_deletion(word, dictionary, substitutes);
}

//THE EXACT SAME AS IN LAB 1

char* delete_char_in_pos(char* word, int pos){
    //new word must be initialized but empty ""
    unsigned long len = strlen(word);
    if (len>0){
        char* new_word = (char*) malloc(sizeof(char)*len); // original length - deleted char + null == original length
        strcpy(new_word, "\0");
        for (int i = 0; i < len; i++){
            if (i != pos){
                char c = word[i];
                strncat(new_word, &c, 1);
            }
        }
        return new_word;
    } else {
        return "";
    }
}

char* insert_char_in_pos(char* word, int pos, char ch){
    unsigned long len = strlen(word);
    if (len>0){
        char* new_word = (char*) malloc(sizeof(char)*(len+2)); // original length + char + null = original length + 2
        strcpy(new_word, "\0");
        for (int i = 0; i < len+1; i++){
            char c;
            if (i == pos){
                c = ch;
                strncat(new_word, &c, 1);
            }
            c = word[i];
            strncat(new_word, &c, 1);
        }
        return new_word;
    } else {
        return "";
    }
}

char* swap_with_consecutive_char(char* word, int pos){
    unsigned long len = strlen(word);
    if (len > 1){
        char* new_word = (char*) malloc(sizeof(char)*(len+1));
        strcpy(new_word, "\0");
        for (int i = 0; i < len; ++i) {
            if (i == pos){
                strncat(new_word, &word[i+1], 1);
                strncat(new_word, &word[i], 1);
                i++;
            } else {
                strncat(new_word, &word[i], 1);
            }
        }
        return new_word;
    } else {
        return "";
    }
}

char* replace_char_by(char* word, int pos, char ch){
    unsigned long len = strlen(word);
    if (len > 0){
        char* new_word = (char*) malloc(sizeof(char)*(len+1));
        strcpy(new_word, "\0");
        for (int i = 0; i < len; ++i) {
            if (i == pos){
                strncat(new_word, &ch, 1);
            } else {
                strncat(new_word, &word[i], 1);
            }
        }
        return new_word;
    } else {
        return "";
    }
}

bool is_vowel(char ch){
    char vowels[VOWELS] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < 5; ++i) {
        if (ch == vowels[i]) return true;
    }
    return false;
}