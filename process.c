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

// Determine when to execute command
// First time: nothing has been run before, file can't be found, run all command
// When update a node, should notify parents to update as well
//(for example, you modified a file after the last time make runs, fstat() tells you when the file is last modified, 
// if such a update (later time stamp) is found, you need to update a node and update from bottom to top (child to parent))

// A dependence item is either the name of another target or the name of a file.
// If dependence name is the name of a file, then the commands in the specification are run if the modification time
// of one of the file is more recent then the modification time of the file named by the target.
// If dependence name is the name of another target, then the commands in the specification are run if that target 
// was out of date and needed to be run.
// After update, need to run the command line again, which is to call process

// new update = run the command again = create process and execute process
// fork(), execvp()
// When you want to run a new command, you will fork a new (child) process and
// then that child process will exec the command.  The parent (creating) process
// will wait until the child has completed.
// Any command that exits with an error (completion code less than zero) terminates the make process.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process.h"

/*
 * execute - run build command in a new process, waiting for its completion, 
 * and getting the return code.
 */
int execute(struct Node *input) {
	// Pointers for file
	FILE *fp;
	
	// Set path to be target
	char path1[1024];
	strcpy(path1, "/");
	strcat(path1, input -> target);
	
	// Try to open target
	fp = fopen(path1, "r");
	
	// If target is found, check its modification time
	if(fp != NULL){
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
					if (dependence_mtime < modification_time) {
						// Pid of child process
						pid_t child_pid;
						
						// Exit status of child process
						int child_status;
						
						// If fork fails, print error message and terminate program
						if ((child_pid = fork()) < 0) {
							fprintf(stderr, "Cannot do fork a child process.\n");
							exit(1);
						}
						// Fork child process
						if (child_pid == 0) {
							// Execute command, if execvp fails, print error message and terminate program
							if (execvp(input -> command, input) < 0) {
								fprintf(stderr, "Cannot do execvp for child process.\n");
								exit(1);
							}
						}
						// Run parent process
						else {
							// Wait for child process
							if (wait(&child_status) < 0) {
								fprintf(stderr, "Cannot do execvp for child process.\n");
								exit(1);
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
		// Pid of child process
		pid_t child_pid;
		
		// Exit status of child process
		int child_status;
		
		// If fork fails, print error message and terminate program
		if ((child_pid = fork()) < 0) {
			fprintf(stderr, "Cannot do fork a child process.\n");
			exit(1);
		}
		// Fork child process
		if (child_pid == 0) {
			// Execute command, if execvp fails, print error message and terminate program
			if (execvp(input -> command, input) < 0) {
				fprintf(stderr, "Cannot do execvp for child process.\n");
				exit(1);
			}
		}
		// Run parent process
		else {
			// Wait for child process
			if (wait(&child_status) < 0) {
				fprintf(stderr, "Cannot do execvp for child process.\n");
				exit(1);
			}
		}
	}
	return 0;
}
