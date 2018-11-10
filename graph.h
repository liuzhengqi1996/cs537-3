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

#define MAXVEX 100

// Structure for graph
typedef struct Graph {
    int num_vertices;
    // List of nodes
    Node **vexs;
    // Adajacency matrix
    int arc[MAXVEX][MAXVEX];
    int iterator;
} Graph;

/*
 * graph - create, update, and access a build specification; build the graph that
 * represents the dependences between build specifications.
 */
Graph *build_graph(struct Node **input);

/*
 * create_tar_node - create a node and initialize with input string structure for a target file.
 */
Node *create_tar_node(struct Node *input, int n);

/*
 * create_file_node - create a node and initialize with input string structure for a non-target file.
 */
Node *create_file_node(char *input);

/*
 * find - find whether a node has been built.
 */
int find(char *input, Node *vexs[MAXVEX]);

/*
 * post_order_traversal - traverse the graph in a bottom-up order and execute commands for the required node
 */
int *post_order_traversal(struct Graph *graph, struct Node *input);

