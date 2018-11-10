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
    int num;
} Node;

/*
 * parser - parse lines in the makefile, split a line into an array of strings,
 * checking whether the line begins with a tab or regular character, and filter
 * out blank lines.
 */
Node **parser(char *path);

/*
 * delete_space - return the string without space.
 */
char *delete_space(char *pStr);
