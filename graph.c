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
	// Create all target nodes
    for (int i=0;i<counter;i++){
        Node* newNode=create_tar_node(input[i]);
        vexs[i]=newNode;
    }
	// Counter for all vertices
    int vex_counter=counter;
    for (int i=0;i<counter;i++){
        // Counter for dependency node
        int dep_count=0;
        while(input[i] ->dependence[dep_count] != NULL){
            dep_count++;
        }
        for (int j= 0;j<dep_count;j++)
            char * dest= string[i] ->dependence [j];
        int find = find(dest,vexs);
	    // Change arc to 1 if the node is connected to its child,
	    // create a file node for non-target node
            if (find == -1) {
                Node * newNode = create_file_node(dest);
                int newvex=vex_counter;
                vexs[vex_counter]=newNode;
                vex_counter++;
                arc[i][newvex]=1;
            }
            else {
                arc[i][find]=1
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
Node *create_tar_node(struct String * input) {
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    
   
	node -> target = input -> target;
	node -> dependence = input -> dependence; 
	node -> command = input -> command;
    
	//node -> next = NULL;
	return node;
}

Node *create_file_node(char * input){
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node -> target = input;
    node -> dependence= NULL;
    node -> command = NULL;
    return Node;
}

/*
 * find - Check if a node has already been visited as a target.
 */
int find ( char* input ,Node** vexs ){
    for (int i=0;i<VEXMAX;i++){
        char *s=vexs[i] -> target;
        if(strcmp(input,s)==0){return i;}
    }
    return -1;
}

/*
 * post_order_traversal - traverse the graph in a bottom-up order and execute each node
 */
void *post_order_traversal(struct Graph *graph, struct Node *input) {
	// Execute the node itself
	execute(input);
	
	int i = 0;
	int j = 0;
	int counter = 0;
	int visited[sizeof(graph.arc)];
	// Execute its unvisited parent node (if there is an edge from parent node to current node),
	// terminate when all nodes are visited
	while (counter != sizeof(graph.arc)) {
		for (i = 0; i < sizeof(graph.arc); i++) {
			for (j = 0; j < sizeof(graph.arc[0]); j++) {
				if (vexs[j] == input && arc[i][j] == 1 && visited[i] != 1) {
					execute(vexs[i]);
					vistied[i] = 1;
					counter++;
				}
			}		
		}
		// Recursively update parent node
		input = vexs[i];
	}
}
