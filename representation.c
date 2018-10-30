////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        representation.c
// Other Files:      main.c, parser.c, parser.h, graph.c, graph.h, 
//                   representation.h, process.c, process.h makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// One node in the build specification graph would represent a target, its dependences, and commands
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