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
extern Node *create_tar_node(struct Node *input);
extern Node *create_file_node(char *input);
extern int find(char *input, Node *vexs[MAXVEX]);
extern int *post_order_traversal(struct Graph *graph, struct Node *input);

/*
 * graph - create, update, and access a build specification; build the graph that 
 * represents the dependences between build specifications.
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
		Node* newNode = create_tar_node(input[i]);
		graph -> vexs[i] = newNode;
	}
	for (int i = counter; i < MAXVEX; i++) {
		graph -> vexs[i] = NULL;
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
			// Change arc to 1 in adajacency matrix if the node is connected to its child,
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
	return graph;
}

/*
 * create_tar_node - create a node and initialize with input string structure for a target file.
 */
Node *create_tar_node(struct Node *input) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	node -> target = input -> target;
	node -> dependence = input -> dependence; 
	node -> command = input -> command;
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
int find(char *input, Node *vexs[MAXVEX]){
    for (int i = 0; i < MAXVEX; i++){
		if (strcmp(input, vexs[i] -> target) == 0) {
			return i;
		}
    }
    return -1;
}

/*
 * post_order_traversal - traverse the graph in a bottom-up order and execute commands for the required node
 */
int *post_order_traversal(struct Graph *graph, struct Node *input) {
	// Sum of number of child nodes the input node has
	int sum_edge = 0;
	// Sum of number of visited child node
	int sum_visited = 0;
	for (int i = 0; i < MAXVEX; i++) {
		for (int j = 0; j < MAXVEX; j++) {
			if (graph -> vexs[i] == input) {
				sum_edge = sum_edge + graph -> arc[i][j];
			}
			if (graph -> vexs[i] == input && graph -> arc[i][j] == 1 && graph -> visited[j] == 1) {
				sum_visited++;
			}
		}
	}
	
	// If all child nodes are visited, execute the node
	if (sum_edge == sum_visited) {
		execute(input);
		return 0;
	}
	
	// Traverse the child node
	for (int i = 0; i < MAXVEX; i++) {
		for (int j = 0; j < MAXVEX; j++) {
			if (graph -> vexs[i] == input && graph -> arc[i][j] == 1 && graph -> visited[j] != 1) {
				graph -> visited[j] = 1;
				post_order_traversal(graph, graph -> vexs[j]);
			}
		}
	}
	return 0;
}
