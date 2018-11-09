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

extern Node ** parser(char *path);

/*
 * parser - parse lines in the makefile, split a line into an array of strings,
 * checking whether the line begins with a tab or regular character, and filter
 * out blank lines, return array of struct String
 */
Node ** parser(char *path) {
    printf("this is func parser\n");
    // Pointers for file
    FILE *fp;
    
    // Open makefile or Makefile
    fp = fopen(path, "r");
    
    
    // If an invalid line (first char is not a number or a letter) is detected,
    // If an invalid line (first char is not a number or a letter) is detected,
    // print error message and terminate the program
    // Otherwise, allocate memory for target, dependence, command
    // print error message and terminate the program
    // Otherwise, allocate memory for target, dependence, command
    // If makefile or Makefile can't be found, report an error
    if(fp == NULL){
        printf("Cannnot find makefile/Makefile\n");
        exit(1);
    }
    else {
        printf("open succesfully in func parser\n");
        
        // Size of input buffer
        int BUFFSIZE = 10240;
        char *buffer = (char*) malloc(sizeof(char) * BUFFSIZE);
        char *temp;
        int lineNum = 1;
        int i = 0;
        
        // Create and allocate memory for String structure
        struct Node **s = (struct Node **) malloc(sizeof(struct Node*) * BUFFSIZE);
        for (int i = 0; i < BUFFSIZE; i++) {
            s[i] = malloc(sizeof(struct Node));
            s[i] -> target = (char *) malloc(sizeof(char) * BUFFSIZE);
            s[i] -> dependence = (char **) malloc(sizeof(char*) * BUFFSIZE);
            s[i] -> command = (char **) malloc(sizeof(char*) * BUFFSIZE);
        }
        
        // Parse target, dependence, command
        // When there is a line to read, store the line in buffer
        while (fgets(buffer,100, fp) != NULL) {
            //printf("buffer:%s\n",buffer);
            // If the current String structure is full, reallocate memory to double its size
            /* if (lineNum == BUFFSIZE) {
             BUFFSIZE = BUFFSIZE * 2;
             struct Node **s = (struct Node **) realloc(s, sizeof(struct Node*) * BUFFSIZE);
             for (int i = 0; i < BUFFSIZE; i++) {
             s[i] = realloc(s[i], sizeof(struct Node));
             }
             }*/
            
            // Skip the blank line
            //
            if (buffer[0] == '\n') {
                continue;
            }
            else if(strstr(buffer,"clean") != NULL) continue;
            else {
                // Check if the line is a target line
                // The target starts on the first character of a line and ends with a ":" character
                if ( strstr(buffer,":") != NULL) {
                    temp = strtok(buffer, ":");
                    printf("target:%s\n",temp);
                    // Increment struct count for a new target
                    if (s[i] -> target != NULL) {i++;}
                    s[i] -> target = temp;
                    // Dependence names are after ":" character and each is separated by one or more spaces
                    int j = 0;
                    while ((s[i] -> dependence[j] = strtok(NULL, " ")) != NULL) {
                        j++;
                    }
                }
                // Check if the line is a command line
                // A command line always starts with a tab character (not spaces)
                else if (buffer[0] == '\t') {
                    printf("buffer:%s",buffer);
                    // Arguments are after tab character and each is separated by one or more spaces or tabs
                    int j = 0;
                    strtok(buffer, "\t");
                    while ((s[i] -> command[j] = strtok(NULL, " \t")) != NULL) {
                        j++;
                    }
                }
                // Otherwise, the line is invalid, print error message and terminate the program
                else {
                    fprintf(stderr, "%d: %s %s\n", lineNum, "Invalid line:", buffer);
                    exit(1);
                }
            }
            lineNum++;
        }
        
        //printf("buffer:%s",buffer);
        printf("0:target:%s",s[2] -> target);
        return s;
    }
}

