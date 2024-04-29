#include "node.h"
#include <limits.h>
#include <stdio.h>

#define TABLESIZE_MSG "Table size: %zu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define THRESHOLD_MSG "Reached threshold: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"

void print_info(Node **htable, size_t table_size, unsigned long threshold) {
	// TODO: walk down the indices of the htable
	
	unsigned long num_entries =0;
	unsigned long longest_chain = 0;
	unsigned long shortest_chain = ULONG_MAX;
	unsigned long reached_threshold = 0; //number of chains longer than or equal to threshold
	unsigned long empty_buckets = 0;
    
	
	// iterate through each chain and update statistics
    
    Node **ht = htable;
	unsigned long bucket_index = 0; //j
    while(bucket_index < table_size){
		unsigned long int node_count = 0; //i 
		Node *ith_front = *(ht+bucket_index);
		while(ith_front != NULL){
			num_entries++;
			node_count++;
			ith_front = ith_front->next;
		}

		if(node_count >longest_chain){
				longest_chain = node_count;
		}
		if (node_count < shortest_chain){
			shortest_chain = node_count;
		}
		if(node_count == 0){
			empty_buckets++;
		}
		if (node_count >= threshold){
				reached_threshold++;
		}
		bucket_index++;
	}

/*for (size_t bucket = 0; bucket < table_size; bucket++){
		Node *ith_front = *(htable + bucket);
		size_t node_count = 1;

		//empty bucket, shortest chain should be 0
		if (ith_front == NULL){
			empty_buckets++;
		}
		else{
			while(ith_front != NULL){
			node_count++;
			num_entries++;
			ith_front = ith_front->next;
			}
			if(node_count >longest_chain){
				longest_chain = node_count;
			}
			if (node_count < shortest_chain){
				shortest_chain = node_count;
			}
			if (node_count > threshold){
				reached_threshold++;
			}
		

		}*/


	
		
	

	//check if empty bucket indicates the shortest chain = 0
	if (empty_buckets >0 && shortest_chain != 0){
		shortest_chain = 0;
	}


	// print out statistics at end
	printf(TABLESIZE_MSG, table_size);
	printf(TOTAL_ENTRIES_MSG, num_entries);
	printf(LONGEST_MSG, longest_chain);
	printf(SHORTEST_MSG, shortest_chain);
	printf(THRESHOLD_MSG, reached_threshold);
	printf(EMPTY_MSG, empty_buckets);

	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
}

