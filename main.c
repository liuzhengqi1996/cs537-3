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
 * main - write a simple version of the make command, read a a "makefile" and
 * follow the specifications in the makefile as to which commands need to be
 * executed.
 */
int main(int argc, char *argv[]) {
    // Look first for a file called "makefile"; if that is found, then it will
    // use that file to run. If it does not find "makefile", then it will look
    // for a file called "Makefile". If neither file is found, then report the
    // error and exit. (For an extra 1 point of credit, you can implement the
    // "-f" option of make to specify a custom file name.)
    
    // If command line arguments does not begin with 537make, print the proper format and exit
    if (argc < 1) {
        fprintf(stderr, "%s\n", "Proper format begins with 537make.\n");
        exit(1);
    }
    
    if(strcmp(argv[0], "537make") != 0) {
        fprintf(stderr, "%s\n", "Proper format starts with 537make.\n");
        exit(1);
    }
    
    // Pointers for file
    FILE *fp;
    
    // Set path to be makefile
    char *path1;
    path1 = "/makefile";
    
    // Try to open makefile
    fp = fopen(path1, "r");
    
    // If makefile is found, use it to run
    if(fp != NULL){
        // If command line contains only 537make
        if (argc == 1){
            Node **parserline = parser(path1);
            Graph *G = build_graph(parserline);
            int n = G -> num_vertices;
            for(int i= 0; i < n; i++) {
                post_order_traversal(G, G -> vexs[n - i + 1]);
            }
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
                }
            }
            Node **parserline = parser(path1);
            Graph *G = build_graph(parserline);
            int finder = find(argv[1], G -> vexs);
            for (int i= G -> num_vertices - 1; i > finder; i--) {
                post_order_traversal(G, G -> vexs[i]);
            }
        }
    }
    // If makefile can't be found, try to open Makefile
    else {
        char *path2;
        path2 = "/Makefile";
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
                int n = G -> num_vertices;
                for(int i = 0; i < n; i++) {
                    post_order_traversal(G, G -> vexs[n - i + 1]);
                }
            }
            // Otherwise, execute the file after 537make
            else {
                Node **parserline = parser(path2);
                Graph *G = build_graph(parserline);
                int finder = find(argv[1], G -> vexs);
                for (int i = G -> num_vertices - 1; i > finder; i--){
                    post_order_traversal(G, G -> vexs[i]);
                }
            }
        }
    }
    return 0;
}
