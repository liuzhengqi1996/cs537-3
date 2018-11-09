////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        parser.h
// Other Files:      main.c, parser.c, graph.c, graph.h, process.c, process.h
//                   makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// Structure for target, dependence, command strings
typedef struct Node {
	char *target;
	char **dependence;
	char ***command;
} Node;

/*
 * parser - parse lines in the makefile, split a line into an array of strings, 
 * store the line into strings after checking whether the line is valid and 
 * filtering out blank lines, return array of struct Node.
 */
Node **parser(char *path);
