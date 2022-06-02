/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tree.h
 * Author: abravo
 *
 * Created on May 27, 2018, 10:48 AM
 */

#ifndef TREE_H
#define TREE_H

#include "utils.h"

typedef struct _Node {
    char data[MAX_WORD_LENGTH];
    struct _Node *left;
    struct _Node *right;
} Node;


typedef struct {
    Node *root;
    int size;
} Tree;


void init_tree(Tree *t);

void clear_tree(Tree *t);

void print_tree_size(Tree *t);

bool insert_into_tree(Tree *t, char *word);

Node *createNode(char *word);

char* find_in_tree(Tree *t, char *word);

Node* insertNode(Node *node, char *word);

Node* deleteNode(Node *root, char *word);

void print_tree(Tree *t);
void printInOrder(Node *node);
void printPreOrder(Node *node);
void printPostOrder(Node *node);

void delete(Tree t, char *word);

#endif /* TREE_H */

