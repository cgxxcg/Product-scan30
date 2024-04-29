#include "node.h"
#include <stdlib.h>

void delete_table(Node **htable, size_t table_size) {
	// TODO: walk through the chains in table
	for (size_t ith_chain= 0; ith_chain < table_size; ith_chain++){
        // TODO: free all the memory associated to each node in each chain
		//free each node & its id, item in the same chain 
		Node *nodeInChain = *(htable + ith_chain);
		while (nodeInChain != NULL){
			Node *nextNode = nodeInChain->next;
            
            free(nodeInChain->id);
            free(nodeInChain->purchased_item);
            free(nodeInChain);

            // Move to the next node
            nodeInChain = nextNode;		}
	*(htable + ith_chain) = NULL;
	}
	// TODO: free the entire table
	free(htable);
}

