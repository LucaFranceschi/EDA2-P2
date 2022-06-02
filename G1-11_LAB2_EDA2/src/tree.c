#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "commons.h"
#include "tree.h"


void init_tree(Tree *t) {
    t->root = NULL;
    t->size = 0;
}
/*
 * Remove all nodes from the memory using Post Order approach
 */
void clearPostOrder(Node *node) {
    // YOUR CODE HERE
}

void clear_tree(Tree *t) {
    clearPostOrder(t->root);
    init_tree(t);
}

Node *createNode(char *word) {
//    printf("Creating node...\n");
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->data, word);
    newNode->left = NULL;
    newNode->right = NULL;
//    printf("Done\n");
    return newNode;
}


Node *insertNode(Node *node, char *word) {
    if (node == NULL) {
//        printf("goes on root!\n");
        node = createNode(word);
    } else {
        if (strcmp(word, node->data) > 0) {
            // YOUR CODE HERE
        } else if (strcmp(word, node->data) < 0) {
            // YOUR CODE HERE
        }
    }
    return node;
}

Node *findNode(Node *node, char *word) {
    // YOUR CODE HERE
}

bool insert_into_tree(Tree *t, char *word) {
    // YOUR CODE HERE

    /*!!! change to true when completed !!!*/
    return TRUE;
}

char *find_in_tree(Tree *t, char *word) {

    Node *elem = findNode(t->root, word);
    return &elem->data;
}

Node* deleteNode(Node *root, char *word){

    // YOUR CODE HERE
}

void print_tree_size(Tree *t) {
    printf("The tree has %d elements.\n", t->size);
}

void printInOrder(Node *node) {
    // YOUR CODE HERE
}
void printPreOrder(Node *node) {
    // YOUR CODE HERE
}
void printPostOrder(Node *node) {
    // YOUR CODE HERE
}


