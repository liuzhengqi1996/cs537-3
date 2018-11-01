////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        graph.c
// Other Files:      main.c, parser.c, parser.h, graph.h, process.c, process.h
//                   makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// Parent: target
// Child: dependence node which can further be a target or a file
// return node (a root node)

// the graph can be an array or linked list to illustrate Adjacency Matrices or Adjacency Lists

// One node would represent a target, its dependences, and commands
// Do post-order traversal with root node as input to evaluate the specifications
// Call process method in post-order traversal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

/*
 * graph - create, update, and access a build specification; build the graph that 
 * represents the dependences between build specifications, and traverse the graph
 * in a bottom-up order to evaluate the specifications (a post-order traversal).
 */
Node *build_graph(struct String **input) {
	
}

/*
 * create_node - create a node and initialize with input string structure.
 */
Node *create_node(struct String *input) {
	struct node *node = (struct Node*) malloc(sizeof(struct Node)); 
	node -> target = input -> target;
	node -> dependence = input -> dependence; 
	node -> command = input -> command; 	
	node -> next = NULL; 
	return node;
}

/*
 * insert - insert a node into the graph.
 */
Node *insert(struct Node *node) {
	
}

