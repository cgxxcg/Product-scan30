#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#define MAX_QUERY_LEN 100
#define MIN_TABLE_SIZE 3
#define DEFAULT_TABLE_SIZE 1873
#define QUERY_SUCCESS_FORMAT "found sale id=%s, purchased_item=%s, cost=%.5f\n"
#define QUERY_FAILURE_FORMAT "could not find sale with id=%s\n"
#define USAGE_STRING "%s [-s threshold] [-t table_size] <filename>\n"

int main(int argc, char **argv) {
	int s_flag = 0;
	size_t table_size = 0;
	// TODO: parse opts with getopt and initialize these variables
	// (see strtoul for parsing unsigned long)
	// handle any bad inputs (missing filename or invalid option flag
	// by printing out the USAGE_STRING to stderr and exiting with failure:
	 
	int opt = 0;
	unsigned long threshold = 0; 
	unsigned long int actual_size = 0;
    char *filename = NULL;
	table_size = DEFAULT_TABLE_SIZE;
	while ((opt = getopt(argc, argv, "s:t:")) != -1) {
		switch (opt) {
			case 's':
			    errno = 0;
			    char *endptr = NULL;
				threshold = strtoul(optarg, &endptr, 10);

				if(endptr == optarg){
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
				}
				else if (errno == ERANGE && threshold == ULONG_MAX){
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
			
				}
				else if (errno != 0 && threshold == 0){
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
				}
				s_flag = 1;
				break;

			case 't':
			errno = 0;
			    char *ptr = NULL;
				actual_size = strtoul(optarg, &ptr, 10);
				if(ptr == optarg){ //missing argument
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
				}
				else if (errno == ERANGE && actual_size == ULONG_MAX){
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
				}
				else if (errno != 0 && actual_size == 0){
					fprintf(stderr, USAGE_STRING, argv[0]); 
					return 0;
				}

				if (actual_size < MIN_TABLE_SIZE){
					table_size = MIN_TABLE_SIZE;
				}
				else if(actual_size > INT_MAX){ 
					fprintf(stderr, "Table size is too big"); 
					return 0;
				}
				else{
					table_size = actual_size;
				}
				break;


			case '?': //option character not in optstring or detects a missing argument
				fprintf(stderr, USAGE_STRING, argv[0]); 
				return 0;

			default:
				fprintf(stderr, USAGE_STRING, argv[0]); 
                return 0;
			}
		
	}

    if (optind >= argc) {
			fprintf(stderr, "Missing filename argument.\n");
			return 0;
		}

	filename = argv[optind];
	


	

	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	Node **htable = calloc(table_size, sizeof(Node*));

	if (htable == NULL) {
		return EXIT_FAILURE;
	}
    
	
	
    //load table 
	if (load_table(htable,table_size,filename) == 0) { 
		fprintf(stderr, "error in load_table\n");
		delete_table(htable, table_size);
		return EXIT_FAILURE;
	}
	

	char query[MAX_QUERY_LEN + 1]; //allocate one more for \0
	char *end;
	// read one line at a time from stdin, do a lookup for that id
	int query_count = 0; 


	while (fgets(query, MAX_QUERY_LEN + 1, stdin) == query) {
		// replace the \n, if it exists (for hashing)
		if ((end = strchr(query, '\n'))) *end = '\0'; // don't change this line

		// TODO: read a line from stdin and perform a lookup
		// if the sale is found, print its contents to stdout
		// using QUERY_SUCCESS_FORMAT
		size_t index = hash(query)%table_size;
		Node **ht = htable;
		Node *lookup_result = node_lookup(*(ht+index), query);

		
		if (lookup_result != NULL) {
            printf(QUERY_SUCCESS_FORMAT, lookup_result->id, 
			 							lookup_result->purchased_item,
										lookup_result->cost);
			query_count++;
        } 
		// if the sale is not found, print a message to **stdout**
		// using QUERY_FAILURE_FORMAT
		//
		// keep track of the number of successful queries
		else {
            printf(QUERY_FAILURE_FORMAT, query );
		}
        
	}
	printf("%d successful queries\n", query_count);

	// if -s called then print stats
	if (s_flag == 1) {
		// TODO: output the stats
		print_info(htable,table_size,threshold);
	}

	// TODO: free all allocated memory associated with the table
	// using delete_table()
	delete_table(htable, table_size);
	return EXIT_SUCCESS;
}


