#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LEN 100
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

bool load_table(Node **htable, size_t table_size, const char *filename) {
	FILE *fp = NULL;
	// TODO: open the file and check that it was successful
    
    fp = fopen(filename,"r");
	if (fp == NULL){
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
		return 0; //false
	}

	// TODO: loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	const char *delim = ",";
	char buf[MAX_LINE_LEN + 1]; // input buffer for fgets


	while (fgets(buf, MAX_LINE_LEN + 1, fp) == buf) {
              
		// TODO: for each line, use strtok to break it into columns

        char *id = strtok(buf, delim);
        char *purchased_item = strtok(NULL, delim);
		char *costPointer = strtok(NULL, delim);
        // Check if any column is missing
        if (id == NULL || purchased_item == NULL ||  costPointer == NULL) {
            fprintf(stderr, "Invalid line format: %s\n", buf);
            continue; // Skip to the next line	
        }
		double cost = atof(costPointer); 

		// TODO: get the corresponding chain for this entry
        unsigned long hash_index = hash(id)%table_size; //string id as input
	    Node **ht = htable;
		// TODO: check that the node doesn't already exist in table
		// handle duplicate 
        if (node_lookup(*(ht+hash_index), id) != NULL){ 
            fprintf(stderr, DUPLICATE_ID_MSG, id);
        }	    
		// TODO: add non-duplicate node to the front of its chain
		else{ 
		    Node *result = make_node(*(ht+hash_index), id, purchased_item, cost); 
			//failed to make new node
			if (result == NULL){
				fprintf(stderr, INSERTION_ERROR_MSG, id);
				fclose(fp);
				return 0;
			}
			*(ht+hash_index) = result;
		}
	}
	fclose(fp);
	return 1;
}

