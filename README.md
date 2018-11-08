# cs537-3
# how to run test?

# [tian@rockhopper-03] (1)$ cd private/cs537/p3/test
# [tian@rockhopper-03] (2)$ ls
537make*                  graph.h             makefile   process.h
advanced_cycle_testcase/  graph.o             parser.c   process.o
basic_cycle_testcase/     linesize_testcase/  parser.h   README
basic_testcase/           main.c              parser.o   simple_testcase/
graph.c                   main.o              process.c  whitespace_testcase/
# [tian@rockhopper-03] (3)$ rm -f *.o 537make
# [tian@rockhopper-03] (4)$ scan-build make
scan-build: Using '/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/clang-8' for static analysis
/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/../libexec/ccc-analyzer -Wall -Wextra -g -c main.c
/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/../libexec/ccc-analyzer -Wall -Wextra -g -c parser.c
/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/../libexec/ccc-analyzer -Wall -Wextra -g -c graph.c
graph.c:115:21: warning: Dereference of undefined pointer value
                if (strcmp(input, vexs[i] -> target) == 0) {
                                  ^~~~~~~~~~~~~~~~~
1 warning generated.
/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/../libexec/ccc-analyzer -Wall -Wextra -g -c process.c
/afs/cs.wisc.edu/s/clang-6.0.1/@sys/bin/../libexec/ccc-analyzer -o 537make main.o parser.o graph.o process.o
scan-build: 1 bug found.
scan-build: Run 'scan-view /tmp/scan-build-2018-11-08-111455-23551-1' to examine bug reports.
# [tian@rockhopper-03] (5)$ cd advanced_cycle_testcase
# [tian@rockhopper-03] (6)$ ../537make
# [tian@rockhopper-03] (7)$ pwd
/u/t/i/tian/private/cs537/p3/test/advanced_cycle_testcase
# [tian@rockhopper-03] (8)$ cd..
cd..: command not found
# [tian@rockhopper-03] (9)$ cd ..
# [tian@rockhopper-03] (10)$ pwd
/u/t/i/tian/private/cs537/p3/test
# [tian@rockhopper-03] (11)$ cd basic_cycle_testcase
# [tian@rockhopper-03] (12)$ ../537make
