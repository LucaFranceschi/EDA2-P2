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
            node->right = insertNode(node->right, word);
        } else if (strcmp(word, node->data) < 0) {
            node->left = insertNode(node->left, word);
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
        t->root = insertNode(t->root, word);
        t->size++;
        return true;
    } else return false;
}

Node *find_in_tree(Tree *t, char *word) {
    Node *elem = findNode(t->root, word);
    return elem; //&?
}

Node* deleteNode(Node *root, char *word){
    if (root == NULL) return NULL;
    if (strcmp(word,root->data) > 0){
        root->right = deleteNode(root->right, word);
    } else if(strcmp(word, root->data) < 0){
        root->left = deleteNode(root->left, word);
    } else{
        if (root->left == NULL) {
            Node* aux = root->right;
            free(root);
            return aux;
        } else if (root->right == NULL) {
            Node* aux = root->left;
            free(root);
            return aux;
        } else {
            Node* aux = find_max(root->left);
            strcpy(root->data, aux->data);
            root->left = deleteNode(root->left, aux->data);
        }
    }
    return root;
}

void print_tree_size(Tree *t) {
    printf("The tree has %d elements.\n", t->size);
}

void printInOrder(Node *node) {
    if (node != NULL) {
        printInOrder(node->left);
        printf("%s\n", node->data);
        printInOrder(node->right);
    }
}
void printPreOrder(Node *node) {
    if (node != NULL) {
        printf("%s\n", node->data);
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}
void printPostOrder(Node *node) {
    if (node != NULL) {
        printPostOrder(node->left);
        printPostOrder(node->right);
        printf("%s\n", node->data);
    }
}

Node* find_parent_of(Node* node, Node* child){
    if (node != NULL){
        if (node->left == child || node->right == child){
            return node;
        } else if(strcmp(child->data, node->data) > 0){
            return find_parent_of(node->right, child);
        } else {
            return find_parent_of(node->left, child);
        }
    } else return NULL;
}
Node* find_max(Node* node){
    if (node->right == NULL){
        return node;
    } else {
        return find_max(node->right);
    }
}