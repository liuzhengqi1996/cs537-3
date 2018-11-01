////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        graph.h
// Other Files:      main.c, parser.c, parser.h, graph.c, process.c, process.h 
//                   makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// Structure for node in graph
typedef struct Node {
	char *target;
	char **dependence;
	char **command;
	struct Node *next;
} Node;

/*
 * graph - create, update, and access a build specification; build the graph that 
 * represents the dependences between build specifications, and traverse the graph
 * in a bottom-up order to evaluate the specifications (a post-order traversal).
 */
Node *build_graph(String input);