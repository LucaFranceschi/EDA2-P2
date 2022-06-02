#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "main.h"
#include "utils.h"
#include "generate_candidates.h"
#include <time.h>

#if defined(__CYGWIN__) || defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
    #define SEP_TAB "\\"
    #define BASE_DATA_DIR "..\\data"
#else
    #define SEP_TAB "/"
    #define BASE_DATA_DIR "../data"
#endif

/*
 * Load the dictionary from a database file
 */
void load_dictionary(Tree *tree, char *file_name) {

    char* filepath = malloc(MAX_PATH_LENGTH * sizeof(char));
    strcpy(filepath, "");
    strcat(filepath, BASE_DATA_DIR);
    strcat(filepath, SEP_TAB);
    strcat(filepath, file_name);

    printf("Loading dictionary from file: %s\n", filepath);

    FILE *fd = fopen(filepath, "r");
    if (fd != NULL) {
        int count = 0;
        char line[MAX_LENGTH];
        while (fgets(line, MAX_LENGTH, fd) != NULL) {

            line[strcspn(line, "\n")] = 0;
            line[strcspn(line, " \n")] = 0;
            line[strcspn(line, "\r")] = 0;
//            printf("- %s \n",line);
            char *word = line;

            if (insert_into_tree(tree, word)) {
                // printf("%s\n", word);
                count++;
            }
        }
        fclose(fd);
        printf("Dictionary loaded!\n");
        printf("There are %d new entries.\n", count);
    } else {
        printf("Error! Could not load data, check file '%s' is not missing.\n", filepath);
    }
    free(filepath);
}

/*
 * Load all the files contained in the data folder
 */
void menu_load_new_dictionary(Tree *tree) {

    clear_tree(tree);
    char file_name[MAX_WORD_LENGTH];

    printf("\n");
    printf("Which file do you want to load?\n");
    scanf("%s", file_name);
    flush_input();

    load_dictionary(tree, file_name);
}

/*
 * Menu find a word in the dictionary
 */
void menu_find_word(Tree *tree) {
    if (tree->size > 0) {
        char word[MAX_WORD_LENGTH];

        scan_line("Enter word: ", "%s", word);
        str_to_lowercase(word);

        if (find_in_tree(tree, word) != NULL) {
            printf("%s Found!\n", word);
        } else {
            printf("Not found!\n");
        }
    } else {
        printf("The dictionary is empty!\n");
        printf("Choose option 1 to load a dictionary or option 3 to add more words.\n");
    }
}

/*
 * Add a word into the dictionary
 */
void menu_add_new_word(Tree *tree) {
    char word[MAX_WORD_LENGTH];
    scan_line("Enter word: ", "%s", word);

    str_to_lowercase(word);

    if (find_in_tree(tree, word) != NULL) {
        printf("%s exists in the dictionary!\n", word);
    } else {
        if (insert_into_tree(tree, word)) {
            printf("New word is added!\n");
        } else {
            printf("Error! The word \"%s\" already exists.\n", word);
        }
    }
}

/*
 * check words by different techniques
 */

void check_spelling_menu(Tree *tree) {

    if (tree->size > 0) {
        char word[MAX_WORD_LENGTH];
        scan_line("Enter word: ", "%s", word);
        str_to_lowercase(word);
        if (find_in_tree(tree, word) != NULL) {
            printf("%s is correct!\n", word);
        } else {
            Tree substitutes;
            generate_candidates(word, tree, &substitutes);
            if(substitutes.size > 0){
                printf("Substitutes:\n");
                printInOrder(substitutes.root);
            }else{
                printf("Substitutes list is empty!\n");
            }
            clear_tree(&substitutes);
        }

    } else {
        printf("Dictionary is empty!\n");
        printf("Choose option 1 to load a dictionary.\n");
    }
}

/*
 * Delete a word in the selected dictionary
 */
void menu_delete_word(Tree *tree) {
    if(tree->size > 0){
        char word[MAX_WORD_LENGTH];
        scan_line("Enter word: ", "%s", word);
        str_to_lowercase(word);

        if (find_in_tree(tree, word) != NULL) {
            tree->root = deleteNode(tree->root, word);
            tree->size--;
            printf("Deleted!\n");
        } else {
            printf("Not found!\n");
        }
//        print_tree(tree);
    }else{
        printf("Dictionary is empty!\n");
        printf("Choose option 1 to load a dictionary.\n");
    }
}

/*
 * Load words from file benchmark_wordlist.txt for benchmarking process
 */
int load_benchmark_wordlist(char** words) {
    char* filepath = (char*)malloc(MAX_PATH_LENGTH*sizeof(char));
    strcpy(filepath, "");
    strcat(filepath, BASE_DATA_DIR);
    strcat(filepath, SEP_TAB);
    strcat(filepath, "benchmark_wordlist.txt");
    FILE *fd = fopen(filepath, "r");

    int nbwords = 0;
    if (fd != NULL) {
        char line[MAX_WORD_LENGTH];
        while (fgets(line, MAX_WORD_LENGTH, fd)) {
            line[strcspn(line, "\n")] = 0;
            line[strcspn(line, " \n")] = 0;
            line[strcspn(line, "\r")] = 0;
            // printf("- %s \n", line);
            strcpy(words[nbwords], line);
            nbwords++;
        }
        fclose(fd);
        free(filepath);
        return nbwords;
    } else {
        printf("Can't load %s file!\n", filepath);
        return 0;
    }
}

/*
 * Benchmarking the
 */
void benchmarking(){
    int MAX_NUM_WORDS = 10000;
    char* words[MAX_NUM_WORDS];
    for(int i=0; i<MAX_NUM_WORDS; i++){
        words[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
    }
    int nbwords = load_benchmark_wordlist(words);
    printf("Number of words: %d\n", nbwords);

    Tree dictionary1;
    Tree dictionary2;
    init_tree(&dictionary1);
    init_tree(&dictionary2);
    load_dictionary(&dictionary1, "engmix_mini.txt");
    load_dictionary(&dictionary2, "engmix_mini_sorted.txt");

    /*
     * Use each word in words to search from the first dictionary
    */
    clock_t start = clock();

    // YOUR CODE HERE

    clock_t end = clock();
    printf("Execution time 1: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

    /*
     * Use each word in words to search from the second dictionary
    */
    start = clock();

    // YOUR CODE HERE

    end = clock();
    printf("Execution time 2: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

    //cleanup the memory
    for(int i=0; i<MAX_NUM_WORDS; i++){
        free(words[i]);
    }
    clear_tree(&dictionary1);
    clear_tree(&dictionary2);
}

/*
 * Main menu
 */
void main_menu(Tree *tree) {

    int option = -1;
    while (option != 0) {
        printf("\n========= Menu ===========\n");
        printf("1. Load a new dictionary\n");
        printf("2. Find a word\n");
        printf("3. Add a new word\n");
        printf("4. Delete a word\n");
        printf("5. Display dictionary (inOrder)\n");
        printf("6. Display dictionary (preOrder)\n");
        printf("7. Display dictionary (postOrder)\n");
        printf("8. Check spelling\n");
        printf("9. Benchmarking\n");
        printf("0. Exit\n");
        printf("==========================\n");
        option = read_int_option("Choose an option: ");
        printf("\n");
        switch (option) {
            case LOAD_DICTIONARY: // Load dictionary
                menu_load_new_dictionary(tree);
                break;
            case FIND_A_WORD: // Find a word
                menu_find_word(tree);
                break;
            case ADD_A_NEW_WORD: // Add new word
                menu_add_new_word(tree);
                break;
            case DELETE_A_WORD: // Delete a word
                menu_delete_word(tree);
                break;
            case IN_ORDER: // print the whole dictionary using inorder
                printInOrder(tree->root);
                print_tree_size(tree);
                break;
            case PRE_ORDER: // print the whole dictionary using preorder
                printPreOrder(tree->root);
                break;
            case POST_ORDER: // print the whole dictionary using postorder
                printPostOrder(tree->root);
                break;
            case CHECK_SPELLING:
                check_spelling_menu(tree);
                break;
            case BENCHMARKING:
                benchmarking();
                break;
            case EXIT: // Exit the program
                printf("Closing The Application...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    }
}


int main(int argc, char *argv[]) {

    Tree T;
    init_tree(&T);
    load_dictionary(&T, "engmix_rand.txt");

    // Display main menu
    main_menu(&T);

    clear_tree(&T);

    return 0;
}
