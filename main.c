////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        main.c
// Other Files:      parser.c, parser.h, graph.c, graph.h, representation.c
//                   representation.h, process.c, process.h makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

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
	
	
	// Use parser to parse the lines in file
	
	
	// Use returned string structure from parser to build the graph that 
	// represents the dependences between build specifications
	
	
	// Traverse the graph in a bottom-up order to evaluate the specifications
	
	
	// Use returned node from graph to create, update, and access a build specification
	
	
	// Run each build command in a new process, wait for its completion, get the return code
	
	
	return 0;
}
