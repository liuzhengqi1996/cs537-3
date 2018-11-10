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

extern Node **parser(char *path);
extern char *delete_space(char *pStr);
extern Node ** parser_clean(char * path);

/*
 * parser - parse lines in the makefile, split a line into an array of strings,
 * checking whether the line begins with a tab or regular character, and filter
 * out blank lines, return array of struct String
 */
Node **parser(char *path) {
	// Pointers for file
	FILE *fp;
	
	// Open makefile or Makefile
	fp = fopen(path, "r");
	
	// If makefile or Makefile can't be found, report an error
	if(fp == NULL){
		printf("Cannnot find makefile/Makefile\n");
		exit(1);
	}
	else {
		// Size of input buffer
		int BUFFSIZE = 1024;
		char *buffer = (char*) malloc(sizeof(char) * BUFFSIZE);
		char *temp;
		int lineNum = 1;
		int i = 0;
		
		// Create and allocate memory for String structure
		struct Node **s = (struct Node**) malloc(sizeof(struct Node*) * BUFFSIZE);
		for (int i = 0; i < BUFFSIZE; i++) {
			s[i] = malloc(sizeof(struct Node));
			s[i] -> target = (char*) malloc(sizeof(char) * BUFFSIZE);
			s[i] -> target = " ";
			s[i] -> dependence = (char**) malloc(sizeof(char*) * BUFFSIZE);
			s[i] -> command =(char***) malloc(sizeof(char**) * BUFFSIZE);
			
			for (int j=0; j < BUFFSIZE; j++) {
				s[i] -> command[j] = (char**) malloc(sizeof(char*) * 200);
			}
		}
		
		// Parse target, dependence, command
		// When there is a line to read, store the line in buffer
		while (fgets(buffer, 100, fp) != NULL) {
			// Skip the blank line
			if (buffer[0] == '\n'||buffer[0]=='#') {
			
				continue;
			}
			else if (strstr(buffer, "clean") != NULL||strstr(buffer,"rm")!=NULL ) {
				size_t len = 1;
				buffer = (char*) calloc(len, 100);
				continue;
			}
			else {
				int l;
				// Check if the line is a target line
				// The target starts on the first character of a line and ends with a ":" character
				if ( strstr(buffer, ":") != NULL) {
					temp = strtok(buffer, ":");
					temp = delete_space(temp);
					
					if (s[i] -> target != NULL) {
						i++;
					}
					s[i] -> target = temp;
					l = 0;
					
					// Dependence names are after ":" character and each is separated by one or more spaces
					int j = 0;
					char *temper;
					while ((temper = strtok(NULL, " ")) != NULL) {
						temper =delete_space(temper);
						s[i] -> dependence[j] = temper;
						j++;
						size_t len = 1;
						buffer = (char*) calloc(len, 100);
					}
				}
				// Check if the line is a command line
				// A command line always starts with a tab character (not spaces)
				else if (buffer[0] == '\t') {
					// Arguments are after tab character and each is separated by one or more spaces or tabs
					int j = 0;
					char *ty = strtok(buffer, " ");
					ty = delete_space(ty);

					s[i] -> command[l][0] = ty;
					j++;
					char *tempri;
                    
					while ((tempri = strtok(NULL, " ")) != NULL) {
						tempri = delete_space(tempri);
						s[i] -> command[l][j] = tempri;
						j++;
					}
					j = j - 1;
					tempri = s[i] -> command[l][j];
					strcat(tempri, "\0");
					s[i] -> command[l][j] = tempri;
					l++;
					size_t len = 1;
					buffer = (char*) calloc(len, 100);
				}
				// Otherwise, the line is invalid, print error message and terminate the program
				else {
					fprintf(stderr, "%d: %s %s\n", lineNum, "Invalid line:", buffer);
					exit(1);
				}
			}
			lineNum++;
		}
		return s;
	}
}

/*
 * delete_space - return the string without space.
 */
char *delete_space(char*s) {
	if (s == NULL) {
		return s;
	}
	
	int i,j;
	j = 0;
	int n = strlen(s);
	char* temp = (char*) malloc(sizeof(char) * n);
	
	for (i = 0; i < n; i++) {
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
			temp[j] = s[i];
			j++;
		}
		if (s[i] == '\n') {
			break;
		}
	}
	return temp;
}


Node ** parser_clean(char * path){
 // Pointers for file
    FILE *fp;

    // Open makefile or Makefile
    fp = fopen(path, "r");	
     	if(fp == NULL){
        printf("Cannnot find makefile/Makefile\n");
        exit(1);
    }
    else {
 //       printf("open succesfully in func parser\n");

        // Size of input buffer
        int BUFFSIZE = 1024;
        char *buffer = (char*) malloc(sizeof(char) * BUFFSIZE);
        char *temp;
        int lineNum = 1;
        int i = 0;

        // Create and allocate memory for String structure
        struct Node **s = (struct Node **) malloc(sizeof(struct Node*) * BUFFSIZE);
        for (int i = 0; i < BUFFSIZE; i++) {
            s[i] = malloc(sizeof(struct Node));
            s[i] -> target = (char *) malloc(sizeof(char) * BUFFSIZE);
            s[i] -> target = " ";
            s[i] -> dependence = (char **) malloc(sizeof(char*) * BUFFSIZE);
            s[i] -> command =(char***) malloc (sizeof(char*)*(BUFFSIZE));
            for(int j=0;j<BUFFSIZE;j++){
                s[i] -> command[j] = (char **) malloc(sizeof(char*) * 200);
            }
        }
 while (fgets(buffer,100, fp) != NULL) {
            if (buffer[0] == '\n'||buffer[0]=='#') {
                continue;
            }
	    if (strstr(buffer,"clean") == NULL && strstr(buffer,"rm") == NULL ){
	      size_t len = 1;
                buffer = (char*) calloc(len,100 );
		continue;
	    
	    }
            else if(strstr(buffer,"clean") != NULL|| strstr(buffer,"rm") != NULL) {
//		    printf("clean:%s",buffer); 
		    int l;
                // Check if the line is a target line
                // The target starts on the first character of a line and ends with a ":" character
                if ( strstr(buffer,":") != NULL) {
                    temp = strtok(buffer, ":");
                    temp=delete_space(temp);
                    if (s[i] -> target != NULL) {i++;}
                    s[i] -> target = temp;
                    l=0;
                    // Dependence names are after ":" character and each is separated by one or more spaces
                    int j = 0;
                    char *temper;
                    while (( temper = strtok(NULL, " ")) != NULL) {
                            //char * temper;
                              // temper = strtok(NULL, " ");

                               temper=delete_space(temper);

                        s[i] -> dependence[j]=temper;
                            j++;
                        size_t len = 1;
                        buffer = (char*) calloc(len,100 );
                    }
                }
                else if (buffer[0] == '\t') {
//                                  printf("buffer:%s",buffer);
                    // Arguments are after tab character and each is separated by one or more spaces or tabs
                    int j = 0;
                    char* ty = strtok(buffer," ");
                    ty=delete_space(ty);

                    s[i] -> command[l][0]=ty;
                    j++;
                    char * tempri;

                    while (( tempri  = strtok(NULL, " ")) != NULL) {
                        tempri=delete_space(tempri);
                            s[i] -> command[l][j] =tempri;
                        j++;
                    }
                    j=j-1;
                    tempri =  s[i] -> command[l][j];
                    strcat(tempri,"\0");
                     s[i] -> command[l][j] =tempri;
                  /*  char * last =strtok(NULL,"\n");
                    delete_space(last);
                    s[i] -> command[l][j]=last;
                    //      printf("%d last:%s\n",j,last);
                    */
                    l++;
		    size_t len = 1;
                buffer = (char*) calloc(len,100 );
                }
	}
	}

return s;
    }


}
