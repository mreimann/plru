# plru
Tree-Based Pseudo LRU Cache Simulation

Created as part of the SJSU CMpE200 class

This program takes a comma delimited list of number as input and outputs the cache state after each write, and the number of cache hits and misses..

Note: Compile with gcc -o plru.c 
      run with ./plru FILENAME

ToDo:	[FIX] The cache replacement for the first cache miss seems to pick the wrong element. 

Sample results for file with data {1,2,3,4,2,2,8,3,5,6}:

Iteration:   1:  1  0  0  0  [Add: 1]
Iteration:   2:  1  2  0  0  [Add: 2]
Iteration:   3:  1  2  3  0  [Add: 3]
Iteration:   4:  1  2  3  4  [Add: 4]
Iteration:   5:  1  2  3  4  [Add: 2]
Iteration:   6:  1  2  3  4  [Add: 2]
Iteration:   7:  1  2  8  4  [Add: 8]
Iteration:   8:  3  2  8  4  [Add: 3]
Iteration:   9:  3  2  8  5  [Add: 5]
Iteration:  10:  3  6  8  5  [Add: 6]

HITS:    2
MISSES:  4
