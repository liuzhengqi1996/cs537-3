////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        process.c
// Other Files:      main.c, parser.c, parser.h, graph.c, graph.h, 
//                   representation.c, representation.h, process.h makefile
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

// new update = run the command again = create process and execute process
// fork(), execvp()
// When you want to run a new command, you will fork a new (child) process and
// then that child process will exec the command.  The parent (creating) process
// will wait until the child has completed.