////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        graph.c
// Other Files:      main.c, parser.c, parser.h, graph.h, representation.c
//                   representation.h, process.c, process.h makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// Parent: target
// Child: dependency node which can further be a target or a file
// return node (maybe a root node)

// Do post-order traversal with root node as input to evaluate the specifications