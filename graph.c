////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        graph.c
// Other Files:      main.c, parser.c, parser.h, graph.h, process.c, process.h
//                   makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// Parent: target
// Child: dependence node which can further be a target or a file
// return node (a root node)

// One node would represent a target, its dependences, and commands
// Do post-order traversal with root node as input to evaluate the specifications
// Call process method in post-order traversal