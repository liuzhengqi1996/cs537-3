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
Graph * build_graph( Node **input) {
    printf("here is function graph\n");
    struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph*));
    graph -> vexs = (Node**) malloc (sizeof(Node)*MAXVEX);
    for(int i=0;i<MAXVEX;i++){
        graph -> vexs[i]=( Node*)malloc (sizeof( Node));
    }
    int ** arc = (int**)malloc(MAXVEX * sizeof (int*));
    for (int i=0;i<MAXVEX;i++){
        arc[i]=(int*)malloc(MAXVEX*sizeof(int));
    }
    
    int counter = 1;
    printf("input:%c\n",input[2] ->target[0] );
    /* for (int i=1;1<1024;i++){
     if (input[counter] -> target != ' '){
     counter++;
     
     }
     
     if (input[counter] -> target != ' '){break;}
     
     }
     */
    while ( input[counter] -> target [0] != ' ' ) {
        counter++;
    }
    counter=counter;
    //printf("input:%c\n",input[20] ->target[0] );
    printf("counter:%d\n",counter);
    graph -> num_vertices = counter;
    printf("vertex_num:%d\n",graph -> num_vertices);
    // Create all target nodes
    for (int i = 0; i < counter; i++) {
        Node* newNode = create_tar_node(input[i],counter-1);
        //graph -> vexs[i]=(struct Node*)malloc (sizeof(struct Node*));
        graph -> vexs[i] = newNode;
    }
    for (int i = counter+1; i < MAXVEX; i++) {
        graph -> vexs[i] = NULL;
    }
    // Counter for all vertices
    int vex_counter = counter;
    for (int i = 1; i < counter; i++) {
        // Counter for dependency node
        int dep_count = 0;
        while(input[i] -> dependence[dep_count] != NULL) {
            dep_count++;
        }
        for (int j = 0; j < dep_count; j++){
            char *dest = input[i] -> dependence[j];
            printf("dest:%s ",dest);
            int finder = find(dest, graph -> vexs);
            printf("finder:%d\n",finder);
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
	/*
    for (int i=0;i<35;i++){
        printf("grap%d:%s\n",i,graph ->vexs[i] -> target);
        //      printf("grap%d:%s:%s %s %s\n",i,graph ->vexs[i] -> target,graph ->vexs[i] ->command[0][0],graph ->vexs[i] ->command[0][1],graph ->vexs[i] ->command[1][0]);
    }
    for (int i=0;i<18;i++){
        //printf("grap%d:%s:%s %s %s\n",i,graph ->vexs[i] -> target,graph ->vexs[i] ->command[0][2],graph ->vexs[i] ->command[1][6],graph ->vexs[i] ->command[2][3]);
    }
	*/
    return graph;
}

/*
 * create_tar_node - create a node and initialize with input string structure for a target file.
 */
Node *create_tar_node(struct Node *input,int n) {
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    
    node -> target = input -> target;
    node -> dependence = input -> dependence;
    node -> command = input -> command;
    node -> num =n;
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
    //printf("we are in finding");
    int v2=1;
    while(vexs[v2] !=NULL  ){
        v2++;
    }
    printf("v2:%d ",v2);
    
    for (int i = 0; i < v2-1; i++){
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
        printf("travese:%s\n",input ->target);
        int num=graph ->vexs[1] ->num +1;
    int n=find(input -> target,graph ->vexs);
        //printf("num is %d\n",n);

  iter++;
    for(int i=1;i<num;i++){
                if (graph ->arc[n][i]==1){
                        iter++;
                        printf("iter:%d\n",iter);
                        if (iter > 100){
                                printf("there might be a cycle\n");

                                exit(-1);
                        }
                        post_order_traversal(graph,graph -> vexs[i] );

                }

        }
        execute(input);
	/* // Sum of number of child nodes the input node has
    int sum_edge = 0;
    // Sum of number of visited child node
    int sum_visited = 0;
    for (int i = 0; i < MAXVEX; i++) {
        for (int j = 0; j < MAXVEX; j++) {
            if (graph -> vexs[i] == input && graph -> arc[i][j] == 1) {
                sum_edge++;
            }
            if (graph -> vexs[i] == input && graph -> arc[i][j] == 1 && graph -> visited[j] == 1) {
                sum_visited++;
            }
        }
    }
    
    // If all child nodes are visited, execute commands for the node
    if (sum_edge == sum_visited) {
        int cmd_counter = 0;
        while (input -> command[cmd_counter] != NULL) {
            cmd_counter++;
        }
        for (int i = 0; i < cmd_counter; i++) {
            execute(input, cmd_counter);
			return 0;
        }
    }
    
    // Traverse the child node
    for (int i = 0; i < MAXVEX; i++) {
        for (int j = 0; j < MAXVEX; j++) {
            if (graph -> vexs[i] == input && graph -> arc[i][j] == 1 && graph -> visited[j] != 1) {
                graph -> visited[j] = 1;
                post_order_traversal(graph, graph -> vexs[j]);
            }
        }
    }*/
    return 0;
}

