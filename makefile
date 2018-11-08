#
# Main File:        main.c
# This File:        makefile
# Other Files:      main.c, parser.c, parser.h, graph.c, graph.h, 
#                   process.c, process.h
# Semester:         CS 537 Fall 2018
# Lecture:          Lec 001
# Authors:          Zhengqi Liu, Tian Zheng
# CS Login:         zhengqi, tian
# NetID:            mliu292, tzheng24
#

CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o parser.o graph.o process.o
	$(CC) -o $(EXE) main.o parser.o graph.o process.o

main.o: main.c parser.h graph.h process.h
	$(CC) $(WARNING_FLAGS) -g -c main.c

parser.o: parser.c parser.h
	$(CC) $(WARNING_FLAGS) -g -c parser.c

graph.o: graph.c parser.h graph.h
	$(CC) $(WARNING_FLAGS) -g -c graph.c
	
process.o: process.c parser.h process.h
	$(CC) $(WARNING_FLAGS) -g -c process.c
	
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
