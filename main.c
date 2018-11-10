////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        main.c
// Other Files:      parser.c, parser.h, graph.c, graph.h, process.c, process.h
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
#include <dirent.h>
#include "parser.h"
#include "graph.h"
#include "process.h"

/*
 * main - look first for a file called "makefile"; use makefile to run if it is 
 * found. Otherwise, look for a file called "Makefile". If neither file is found,
 * then report the error and exit. Then, parse the file and build a graph to
 * represent the dependences between build specifications, and traverse the graph
 * in a bottom-up order to evaluate the specifications and run each build command
 * in a new process.
 */
int main(int argc, char *argv[]) {
    // Pointers for file
    FILE *fp;
	
    // Set path to be makefile
	char *path1;
	path1 = "makefile";
	
    // Try to open makefile
	fp = fopen(path1, "r");
	
	// If makefile is found, use it to run
	if(fp != NULL){
		// If command line contains only 537make
		int BUFFSIZE=1024;
 struct Node **parserline = (struct Node **) malloc(sizeof(struct Node*) * BUFFSIZE);
                for (int i = 0; i < BUFFSIZE; i++) {
                        parserline[i] = malloc(sizeof(struct Node));
                        parserline[i] -> target = (char *) malloc(sizeof(char) * BUFFSIZE);
                        parserline[i] -> dependence = (char **) malloc(sizeof(char*) * BUFFSIZE);
                        parserline[i] -> command =(char***) malloc (sizeof(char*)*(BUFFSIZE));
                        for(int j=0;j<BUFFSIZE;j++){
                        parserline[i] -> command[j] = (char **) malloc(sizeof(char*) * 200);
                	        }

		                        }
		if (argc == 1){

			Node ** parserline = parser(path1);
			printf("mian fun tar:%s\n",parserline[1] ->target);
			printf("parser success\n");
			Graph *G = build_graph(parserline);
			printf("graph success\n");
			post_order_traversal(G, G -> vexs[1]);
			printf("travesel success\n");
			}
		
		// Otherwise, execute the file after 537make
		else {
			if (strcmp(argv[1], "clean") == 0) {
				if (argc > 2) {
					for (int i = 2; i < argc; i++) {
						if (remove(argv[i]) < 0) {
							fprintf(stderr, "%s\n", "Cannnot remove file.");
							exit(1);
						}
					}
					return 0;
				}
				else {
					DIR *dir;
					struct dirent *de;     
					dir = opendir ("./");
					if (dir != NULL) {
						while ((de = readdir(dir)) != NULL) {
						int length = strlen(de -> d_name);
						if (strncmp(de -> d_name + length - 2, ".o", 2) == 0) {
							if (remove(de -> d_name) < 0) {
								fprintf(stderr, "%s\n", "Cannnot remove file.");
								exit(1);
							}
						}
					}
					closedir (dir);
					}
					return 0;
				}
			}
			Node **parserline = parser(path1);
			Graph *G = build_graph(parserline);
			int finder = find(argv[1], G -> vexs);
			post_order_traversal(G, G -> vexs[finder]);
        }
	}
	// If makefile can't be found, try to open Makefile
	else {
		char *path2;
		path2 = "Makefile";
		fp = fopen(path2, "r");
		if(fp == NULL){
			fprintf(stderr, "%s\n", "Cannnot find makefile or Makefile.");
			exit(1);
		}
		// If Makefile is found, use it to run
		else {
			// If command line contains only 537make
			if (argc == 1) {
				Node **parserline = parser(path2);
				Graph *G = build_graph(parserline);
				post_order_traversal(G, G -> vexs[0]);
			}
			// Otherwise, execute the file after 537make
            else {
				Node **parserline = parser(path2);
				Graph *G = build_graph(parserline);
				int finder = find(argv[1], G -> vexs);
				post_order_traversal(G, G -> vexs[finder]);
			}
		}
	}                                           
	return 0;
}
