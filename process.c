////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        process.c
// Other Files:      main.c, parser.c, parser.h, graph.c, graph.h, process.h 
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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "parser.h"
#include "graph.h"
#include "process.h"

extern void execute(struct Node *input);

/*
 * execute - run build command in a new process, waiting for its completion, 
 * and getting the return code.
 */
void execute(struct Node *input) {
	// Pointers for file
	FILE *fp;
	
	// Set path to be target
	char path1[1024];
	strcpy(path1, "/");
	strcat(path1, input -> target);
	
	// Try to open target
	fp = fopen(path1, "r");
	
	// If target is found, check its modification time
	if (fp != NULL) {
		struct stat file;
		// If stat fails, print error message and terminate program
		if (stat(path1, &file) == -1) {
			fprintf(stderr, "Cannot do stat to get file status.\n");
			exit(1);
		}
		// If a dependence has earlier modification time, run command
		else {
			time_t modification_time = file.st_mtime;
			
			int i = 0;
			while (input -> dependence[i] != NULL) {
				char path2[1024];
				strcpy(path2, "/");
				strcat(path2, input -> dependence[i]);
				struct stat dfile;
				// If the dependence file exists and its modification time can be
				// found, compare it to the modification time of target file
				if (stat(path1, &dfile) == 0) {
					time_t dependence_mtime = file.st_mtime;
					
					// If the dependence file has earlier modification time, 
					// then run command
					if (difftime(dependence_mtime, modification_time) > 0) {
						int cmd_counter = 0;
						
						while (input -> command[cmd_counter][0] != NULL) {
							cmd_counter++;
						}
						
						for (int j = 0; j < cmd_counter; j++) {
							// Pid of child process
							pid_t child_pid;
							
							// Exit status of child process
							int child_status;
							
							// If fork fails, print error message and terminate program
							if ((child_pid = fork()) < 0) {
								fprintf(stderr, "Cannot do fork a child process.\n");
								printf("Error: %s\n", strerror(errno));
								exit(1);
							}
							
							// Run child process
							if (child_pid == 0) {
								// Execute command, if execvp fails, print error message and terminate program
								if (execvp(input -> command[j][0], input -> command[j]) < 0) {
									fprintf(stderr, "Cannot do execvp for child process.\n");
									printf("Error: %s\n", strerror(errno));
									exit(1);
								}
							}
							// Run parent process
							else {
								// Wait for child process
								if (wait(&child_status) < 0) {
									fprintf(stderr, "Cannot wait for process completion.\n");
									printf("Error: %s\n", strerror(errno));
									exit(1);
								}
							}
						}
					}
				}
				i++;
			}
		}
	}
	// If target can't be found, then run command
	else {
		int cmd_counter = 0;
        while (input -> command[cmd_counter][0] != NULL) {
            cmd_counter++;
        }
		
        for (int i = 0; i < cmd_counter; i++) {
			// Pid of child process
			pid_t child_pid;
			
			// Exit status of child process
			int child_status;
			
			// If fork fails, print error message and terminate program
			if ((child_pid = fork()) < 0) {
				fprintf(stderr, "Cannot do fork a child process.\n");
				printf("Error: %s\n", strerror(errno));
				exit(1);
			}

			// Run child process
			if (child_pid == 0) {
				// Execute command, if execvp fails, print error message and terminate program
				if (execvp(input -> command[i][0], input -> command[i]) < 0) {
					fprintf(stderr, "Cannot do execvp for child process.\n");
					printf("Error: %s\n", strerror(errno));
					exit(1);
				}
			}
			// Run parent process
			else {
				// Wait for child process
				if (wait(&child_status) < 0) {
					fprintf(stderr, "Cannot wait for process completion.\n");
					printf("Error: %s\n", strerror(errno));
					exit(1);
				}
			}
        }
	}
}
