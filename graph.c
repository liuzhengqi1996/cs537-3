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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "graph.h"
#include "process.h"

extern Graph *build_graph(struct Node **input);
extern Node *create_tar_node(struct Node *input,int n);
extern Node *create_file_node(char *input);
extern int find(char *input, Node **vexs);
extern int *post_order_traversal(struct Graph *graph, struct Node *input);

/*
 * graph - create, update, and access a build specification; build the graph that
 * represents the dependences between build specifications.
 */
Graph *build_graph(Node **input) {
	// Allocate memory for graph
	struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph -> vexs = (Node**) malloc (sizeof(Node*) * MAXVEX);
	
	for (int i = 0; i < MAXVEX; i++) {
		graph -> vexs[i] = (Node*) malloc(sizeof( Node));
	}
	
	int **arc = (int**) malloc(MAXVEX * sizeof(int*));
	for (int i = 0; i < MAXVEX; i++) {
		arc[i] = (int*) malloc(MAXVEX * sizeof(int));
	}
	
	// Count number of vertices
	int counter = 1;
	while (input[counter] -> target[0] != ' ') {
		counter++;
	}
	graph -> num_vertices = counter;
	
	// Create all target nodes
	for (int i = 0; i < counter; i++) {
		Node *newNode = create_tar_node(input[i], counter - 1);
		graph -> vexs[i] = newNode;
	}
	for (int i = counter + 1; i < MAXVEX; i++) {
		graph -> vexs[i] = NULL;
	}
	
	int vex_counter = counter;
	for (int i = 1; i < counter; i++) {
		// Count number of dependency node
		int dep_count = 0;
		while (input[i] -> dependence[dep_count] != NULL) {
			dep_count++;
		}
		for (int j = 0; j < dep_count; j++){
			char *dest = input[i] -> dependence[j];
			int finder = find(dest, graph -> vexs);
			// If the node has not been built
			if (finder == -1) {
				// create a file node for non-target node
				Node *newNode = create_file_node(dest);
				int newvex = vex_counter;
				graph -> vexs[vex_counter] = newNode;
				vex_counter++;
				// Change arc to 1 in adajacency matrix when the node is connected to its child
				graph -> arc[i][newvex] = 1;
			}
			// If the node has been built
			else {
				// Change arc to 1 in adajacency matrix when the node is connected to its child
				graph -> arc[i][finder] = 1;
			}
		}
	}
	return graph;
}

/*
 * create_tar_node - create a node and initialize with input string structure for a target file.
 */
Node *create_tar_node(struct Node *input, int n) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node -> target = input -> target;
	node -> dependence = input -> dependence;
	node -> command = input -> command;
	node -> num = n;
	return node;
}

/*
 * create_file_node - create a node and initialize with input string structure for a non-target file.
 */
Node *create_file_node(char *input){
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node -> target = input;
	node -> dependence = NULL;
	node -> command = NULL;
	return node;
}

/*
 * find - find whether a node has been built.
 */
int find(char *input, Node **vexs){
	int v2 = 1;
	while (vexs[v2] != NULL) {
		v2++;
	}
	
	for (int i = 0; i < v2 - 1; i++) {
		char * s = vexs[i] -> target;
		if (strcmp(input, s) == 0) {
			return i;
		}
	}
	return -1;
}

/*
 * post_order_traversal - traverse the graph in a bottom-up order and execute commands for the required node
 */
int *post_order_traversal(struct Graph *graph, struct Node *input) {
	int num = graph -> vexs[1] -> num + 1;
	int n = find(input -> target, graph -> vexs);
	graph -> iterator++;
	
	for (int i = 1; i < num; i++) {
		if (graph -> arc[n][i]==1) {
			graph -> iterator++;
			if (graph -> iterator > 100) {
				fprintf(stderr, "There is a cycle, terminate the program.\n");
				exit(1);
			}
		post_order_traversal(graph, graph -> vexs[i]);
		}
	}
	execute(input);
	
    return 0;
}
