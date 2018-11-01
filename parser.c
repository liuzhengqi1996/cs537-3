////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        parser.c
// Other Files:      main.c, parser.h, graph.c, graph.h, process.c, process.h
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

extern String *parser(char path);

/*
 * parser - parse lines in the makefile, split a line into an array of strings, 
 * checking whether the line begins with a tab or regular character, and filter
 * out blank lines, return array of struct String
 */
String **parser(char path) {
	// Pointers for file
	FILE *fp;

	// Open makefile or Makefile
	fp = fopen(path, "r");
	
	// If makefile or Makefile can't be found, report an error
	if(fp == NULL){
		printf("Cannnot find makefile/Makefile\n");
		exit(1);
	} else {
		// Size of input buffer
		const int BUFFSIZE = 1024;
		char *buffer = (char*) malloc(sizeof(char) * BUFFSIZE);
		int lineNum = 1;
		int i = 0;
		
		// Create and allocate memory for String structure
		struct String **s = (struct String **) malloc(sizeof(struct String*) * BUFFSIZE);
		for (int i = 0; i < BUFFSIZE; i++) {
			s[i] = malloc(sizeof(struct String));
		}
		
		// Parse target, dependence, command
		// When there is a line to read, store the line in buffer
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			// If the current String structure is full, reallocate memory to double its size
			if (lineNum == BUFFSIZE) {
				BUFFSIZE = BUFFSIZE * 2;
				struct String **s = (struct String **) realloc(s, sizeof(struct String*) * BUFFSIZE);
				for (int i = 0; i < BUFFSIZE; i++) {
					s[i] = realloc(s[i], sizeof(struct String));
				}
			}
			
			// Skip the blank line
			if (buffer[0] == '\n') {
				break;
			}
			// If an invalid line (first char is not a number or a letter) is detected, 
			// print error message and terminate the process
			else if (!((buffer[0] >= '0' && buffer[0] <= '9') || buffer[0] >= 'A' && buffer[0] <= 'Z' || buffer[0] >= 'a' && buffer[0] <= 'z')) {
				fprintf(stderr, "%d: %s %s\n", lineNum, "Invalid line:", buffer);
				exit(1);
			}
			// Otherwise, allocate memory for target, dependence, command
			else {
				s[i] -> target = (char *) malloc(sizeof(char) * BUFFSIZE);
				s[i] -> dependence = (char **) malloc(sizeof(char*) * BUFFSIZE);
				s[i] -> command = (char **) malloc(sizeof(char*) * BUFFSIZE);
				
				// Check if the line is a target line
				// The target starts on the first character of a line and ends with a ":" character
				else if ((s -> target = strtok(buffer, ":")) != NULL) {
					// Dependence names are after ":" character and each is separated by one or more spaces
					int j = 0;
					while ((s -> dependence[j] = strtok(NULL, " ")) != NULL) {
						j++;
					}
				}
				// Check if the line is a command line
				// A command line always starts with a tab character (not spaces)
				else if ((s -> target = strtok(buffer, "\t")) != NULL) {
					// Arguments are after tab character and each is separated by one or more spaces or tabs
					int j = 0;
					while ((s -> command[j] = strtok(NULL, " \t")) != NULL) {
						j++;
					}
				}
			}
			lineNum++;
		}
		return s;
	}
}
