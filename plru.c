/*
* Tree-Based Pseudo LRU Cache Simulation
*
* Simulate a tree-based pseudo Least Recently Used (PLRU) cache.
*  
* This program takes a comma delimited list of number as input and outputs the cache 
* state after each write, and the number of cache hits and misses.
*
* Note: Compile with gcc -o plru.c 
*       run with ./plru FILENAME
*
* ToDo:	[FIX] The cache replacement for the first cache miss seems to pick the wrong element. 
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define DELIM ","
#define CACHE_SIZE 4
#define PLRU_WAY 4

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Missing filename.\n"); 
		return EXIT_FAILURE;
	}

	FILE *fp = fopen(argv[1], "r");
	
	if (!fp) {
		printf("Invalid filename: %s\n", argv[1]); 
		return EXIT_FAILURE;
	}
	
	int cache[CACHE_SIZE]	= {0};
	int nodes		= 0;	// Stores each node as a bit in an int. Modify to allow caches of size N	
	int linesUsed		= 0;
	int hits		= 0;
	int iteration		= 0;
	int misses		= 0;
	char buffer[255];
	char *token;
	
	fscanf(fp, "%s", buffer);
	token = strtok(buffer, DELIM);

	while (token) {
		iteration++;
		int number = atoi(token);
		
		// Find:
		int found = -1;
		int counter;		
		for (counter = 0; counter < CACHE_SIZE && found < 0; counter++) {
			if (cache[counter] == number) {

				// Read:
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == counter)
					nodes = (nodes & 1) | 6;
				if (1 == counter)
					nodes = (nodes & 1) | 4;
				if (2 == counter)
					nodes = (nodes & 2) | 1;
				if (3 == counter)
					nodes = (nodes & 2) | 0;
				
				found = counter;
				hits++;
			}
		}	
				
		// Write:
		if (found == -1) {

			int currLine = 0;

			if (linesUsed < CACHE_SIZE) {
				currLine = linesUsed;
				linesUsed++;
			}
			else {
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == (nodes & 6))
					currLine = 0;
				else if (2 == (nodes & 6))
					currLine = 1;
				else if (4 == (nodes & 5))
					currLine = 2;
				else if (5 == (nodes & 5))
					currLine = 3;
				
				misses++;
			}
	
			cache[currLine] = number;

			// Update Nodes for last access (same as read, move to function):
			// nodes=00x -> line 0
			// nodes=01x -> line 1
			// nodes=1x0 -> line 2
			// nodes=1x1 -> line 3
			if (0 == currLine)
				nodes = (nodes & 1) | 6;
			if (1 == currLine)
				nodes = (nodes & 1) | 4;
			if (2 == currLine)
				nodes = (nodes & 2) | 1;
			if (3 == currLine)
				nodes = (nodes & 2) | 0;
		}

		// Print Cache Status
		printf("Iteration: %3d: ", iteration);
		for (counter = 0; counter < CACHE_SIZE; counter++) {
			printf("%2d ", cache[counter]);
		}
		printf(" [Add: %d]\n", number);

		// Get next token from file
		token = strtok(NULL, DELIM);
	}
	
	fclose(fp);
	printf("\nHITS:   %2d\nMISSES: %2d\n\n", hits, misses);

	return EXIT_SUCCESS;
}	
