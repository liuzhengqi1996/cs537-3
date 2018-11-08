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
#include "graph.h"
#include "process.h"

extern Graph *build_graph(struct Node **input);
extern Node *create_tar_node(struct Node *input);
extern Node *create_file_node(char *input);
extern int find(char *input, Node *vexs[MAXVEX]);
extern int *post_order_traversal(struct Graph *graph, struct Node *input);

/*
 * build_graph - create, update, and access a build specification; build the graph that 
 * represents the dependences between build specifications, and traverse the graph
 * in a bottom-up order to evaluate the specifications (a post-order traversal).
 */
Graph *build_graph(struct Node **input) {
	struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
	int counter = 0;
	while (input[counter] != NULL) {
		counter++;
	}
	graph -> num_vertices = counter;
	// Create all target nodes
	for (int i = 0; i < counter; i++) {
		Node* newNode=create_tar_node(input[i]);
		graph -> vexs[i] = newNode;
	}
	// Counter for all vertices
	int vex_counter = counter;
	for (int i = 0; i < counter; i++) {
		// Counter for dependency node
		int dep_count = 0;
		while(input[i] -> dependence[dep_count] != NULL) {
		    dep_count++;
		}
		for (int j = 0; j < dep_count; j++){
			char *dest = input[i] -> dependence[j];
			int finder = find(dest, graph -> vexs);
			// Change arc to 1 if the node is connected to its child,
			// create a file node for non-target node
			if (finder == -1) {
				Node *newNode = create_file_node(dest);
				int newvex = vex_counter;
				graph -> vexs[vex_counter] = newNode;
				vex_counter++;
				graph -> arc[i][newvex] = 1;
			}
			else {
				graph -> arc[i][finder] = 1;
			}
		}
	} 

    /*
	graph -> adjacency_list = malloc(counter * sizeof(struct Node*));
    int i;
    for (i=0;i<counter;i++){
        char *s=input[i] -> target;
        graph -> adjacency_list[s]=NULL;
        
    }*/
	return graph;
}

/*
 * create_node - create a node and initialize with input string structure.
 */
Node *create_tar_node(struct Node *input) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node -> target = input -> target;
	node -> dependence = input -> dependence; 
	node -> command = input -> command;
	return node;
}

Node *create_file_node(char *input){
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node -> target = input;
    node -> dependence = NULL;
    node -> command = NULL;
    return node;
}

/*
 * find - Check if a node has already been visited as a target.
 */
int find(char *input, Node *vexs[MAXVEX]){
    for (int i = 0; i < MAXVEX; i++){
		//char *s = vexs[i] -> target;
		if (strcmp(input, vexs[i] -> target) == 0) {
			return i;
		}
    }
    return -1;
}

/*
 * post_order_traversal - traverse the graph in a bottom-up order and execute each node
 */
int *post_order_traversal(struct Graph *graph, struct Node *input) {
	if (graph -> num_visited == MAXVEX) {
		execute(input);
	}
	
	for (int i = 0; i < MAXVEX; i++) {
		for (int j = 0; j < MAXVEX; j++) {
			if (graph -> vexs[j] == input && graph -> arc[i][j] == 1 && graph -> visited[i] != 1) {
				graph -> visited[i] = 1;
				graph -> num_visited++;
				post_order_traversal(graph, graph -> vexs[i]);
			}
		}
	}
	return 0;
}
