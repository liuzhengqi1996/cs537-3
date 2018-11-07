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
	char *vertex;
	char **dependence;
	char **command;
	struct Node *next;
} Node;

// Structure for graph
typedef struct Graph {
	int num_vertices;
    Node * vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
  
	//struct Node **adjacency_list;
   
} Graph;

/*
 * graph - create, update, and access a build specification; build the graph that 
 * represents the dependences between build specifications, and traverse the graph
 * in a bottom-up order to evaluate the specifications (a post-order traversal).
 */
Graph *build_graph(struct String **input);

/*
 * create_tar_node - create a node and initialize with input string structure for a target file.
 */
Node *create_tar_node(struct String * input);


/*
* create_create_node - create a node and initialize with input string structure for a non-target file.
*/
Node *create_file_node(char * input);

// findout whether a point has been built
int find ( char* input ,Node** vexs );
