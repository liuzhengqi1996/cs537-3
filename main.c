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

/*
 * main - write a simple version of the make command, read a a "makefile" and
 * follow the specifications in the makefile as to which commands need to be 
 * executed.
 */
int main() {
	// Look first for a file called "makefile"; if that is found, then it will 
	// use that file to run. If it does not find "makefile", then it will look
	// for a file called "Makefile". If neither file is found, then report the
	// error and exit. (For an extra 1 point of credit, you can implement the 
	// "-f" option of make to specify a custom file name.)
	
	// Pointers for file
	FILE *fp;
	
	// Set path to be makefile
	char path1[30];
	strcpy(path1, "/makefile");
	
	// Try to open makefile
	fp = fopen(path1, "r");
	
	// If makefile is found, use it to run
	if(fp != NULL){
		// Do the steps below
	}
	// If makefile can't be found, try to open Makefile
	else {
		char path2[30];
		strcpy(path2, "/Makefile");
		fp = fopen(path2, "r");
		if(fp == NULL){
			fprintf(stderr, "%s\n", "Cannnot find makefile or Makefile.");
			exit(1);
		}
		// If Makefile is found, use it to run
		else {
			// Do the steps below
		}
	}
	
	// Use parser to parse the lines in file
	
	
	// Use returned string structure from parser to build the graph that 
	// represents the dependences between build specifications
	
	
	// Traverse the graph in a bottom-up order to evaluate the specifications
	
	
	// Use returned node from graph to create, update, and access a build specification
	
	
	// Run each build command in a new process, wait for its completion, get the return code
	
	
	return 0;
}
