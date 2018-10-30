////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        parser.c
// Other Files:      main.c, parser.h, graph.c, graph.h, representation.c
//                   representation.h, process.c, process.h makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

extern String *parser(char path);

/*
 * parser - parse lines in the makefile, split a line into an array of strings, 
 * checking whether the line begins with a tab or regular character, and filter
 * out blank lines, return array of struct String
 */
String *parser(char path) {
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
		char buffer[BUFFSIZE];
		int lineNum = 1;
		
		// Create and allocate memory for String structure
		String *s = (String *) malloc(sizeof(String));
		char targetString[BUFFSIZE];
		s -> target = targetString;
		s -> dependence = (char *) malloc(sizeof(char) * BUFFSIZE);
		s -> command = (char *) malloc(sizeof(char) * BUFFSIZE);
		
		// Parse target, dependence, command
		// When there is a line to read, store the line in buffer
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			// Check if the line is a target line
			// The target starts on the first character of a line and ends with a ":" character
			if ((s -> target = strtok(buffer, ":")) != NULL) {
				// Dependence names are after ":" character and each is separated by one or more spaces
				int i = 0;
				while ((s -> dependence[i] = strtok(NULL, " ")) != NULL) {
					i++;
				}
			}
			// Check if the line is a command line
			// A command line always starts with a tab character (not spaces)
			else if ((s -> target = strtok(buffer, "\t")) != NULL) {
				// Arguments are after tab character and each is separated by one or more spaces or tabs
				int i = 0;
				while ((s -> command[i] = strtok(NULL, " \t")) != NULL) {
					i++;
				}
			}
			// Skip the blank line
			else if (buffer[0] == '\n') {
				break;
			}
			// Print error message for invalid line, terminate the process
			else {
				fprintf(stderr, "%d: %s %s\n", lineNum, "Invalid line:", buffer);
				exit(1);
			}
			lineNum++;
		}
		return s;
	}
}
