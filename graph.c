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
Graph *build_graph(struct String **input) {
	struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
	int counter = 0;
	while (input[counter] != NULL) {
		counter++;
	}
	graph -> num_vertices = counter;
	graph -> adjacency_list = malloc(counter * sizeof(struct Node*));
    int i;
    for (i=0;i<counter;i++){
        char *s=input[i] -> target;
        graph -> adjacency_list[s]=NULL;
        
    }
	return graph;
}

/*
 * create_node - create a node and initialize with input string structure.
 */
Node *create_node(char * input) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node -> vertex = char;
	/*node -> target = input -> target;
	node -> dependence = input -> dependence; 
	node -> command = input -> command;
     */
	node -> next = NULL; 
	return node;
}

/*
 * add_edge - add edges between two nodes from parent (target) to its child
 * (dependence node).
 */
void *add_edge(struct Graph *graph, struct String **input) {
	int counter = 0;
	while (input[counter] != NULL) {
		counter++;
	}
    for (int i=0; i<counter;i++){
        char *src=input[i] -> target;
        int dep_count=0;
        while(input[i] ->dependence[dep_count] != NULL){
            dep_count++;
        }
        for (int j=0;j<dep_count;j++){
            char* dest=input[i] -> dependence[j];
            struct Node* newNode=create_node(dest);
            newNode -> next =graph -> adjacency_list[dest];
            graph -> adjacency_list[dest]=newNode;
            
                                    }
        
        
    }
    
    
	/*int i = 0;
	int j = 0;
	int k = 0;
	// incomplete...
	while (1) {
		// If a dependence is not the same as the subsequent target, check the next line
		if (strcmp(input[i] -> dependence[j], input[i + 1] -> target[k]) != 0) {
			k++;
		}
	}*/
}
