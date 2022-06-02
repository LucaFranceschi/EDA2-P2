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
    if (node != NULL){
        clearPostOrder(node->left);
        clearPostOrder(node->right);
        free(node);
    }
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
            //node->right = createNode(word);
            return insertNode(node->right, word);
        } else if (strcmp(word, node->data) < 0) {
            //node->left = createNode(word);
            return insertNode(node->left, word);
        }
    }
    return node;
}

Node *findNode(Node *node, char *word) {
    if (node != NULL){
        if (strcmp(node->data, word) == 0){
            return node;
        } else if(strcmp(word, node->data) > 0){
            return findNode(node->right, word);
        } else {
            return findNode(node->left, word);
        }
    } else return NULL;
}

bool insert_into_tree(Tree *t, char *word) {
    if (findNode(t->root, word) == NULL){
        insertNode(t->root, word);
        t->size++;
        return true;
    } else return false;
}

char *find_in_tree(Tree *t, char *word) {

    Node *elem = findNode(t->root, word);
    return elem->data; //&?
}

Node* deleteNode(Node *root, char *word){ //return the root
    Node* elem = findNode(root, word);
    if (elem != NULL){
        if (elem->left == NULL && elem->right == NULL){
            free(elem);// ni idea
        }
    } else return NULL;
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


