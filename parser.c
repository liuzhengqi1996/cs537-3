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
 * out blank lines.
 */
String *parser(char path) {
	// Get the path (directory + filename) from main to open file
	
	// Parse target, dependency, command
}
