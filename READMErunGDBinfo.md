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

# [tian@rockhopper-03] (9)$ cd ..
# [tian@rockhopper-03] (10)$ pwd
/u/t/i/tian/private/cs537/p3/test
# [tian@rockhopper-03] (11)$ cd basic_cycle_testcase
# [tian@rockhopper-03] (12)$ ../537make

# [tian@rockhopper-03] (31)$ gdb ../537make
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ../537make...done.
# (gdb) run ../537make
Starting program: /afs/cs.wisc.edu/u/t/i/tian/private/cs537/p3/test/537make ../537make
[Inferior 1 (process 23834) exited normally]
# use GDB breakpoints
# (gdb) break graph.c:post_order_traversal
# (gdb) break process.c:execute

