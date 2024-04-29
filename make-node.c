#include "node.h"
#include <stdlib.h>
#include <string.h>


Node *make_node(Node *front, char *id, char *purchased_item, double cost) {
	// TODO: create a node, copy in the parameter fields
	// make sure that you do a deep copy

	Node *new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL){
		free(new_node);
		return NULL;
	}

	new_node->id = (char *)malloc(strlen(id) + 1);
    new_node->purchased_item = (char *)malloc(strlen(purchased_item) + 1);
	new_node->next = NULL;

	if (new_node->id == NULL && new_node->purchased_item == NULL ){
		free(new_node);
		free(new_node->id);
		free(new_node->purchased_item);
		return NULL;
		
	}
	if (new_node->id == NULL && new_node->purchased_item != NULL ){
		free(new_node->purchased_item);
		free(new_node);
		return NULL;
	}

	if (new_node->id != NULL && new_node->purchased_item == NULL){
		free(new_node->id);
		free(new_node);
        return NULL;
	}
 
    //deep copy 
	strcpy(new_node->id, id);  //(detination, source)
    strcpy(new_node->purchased_item, purchased_item);
	new_node->cost = cost;
	// TODO: link the new node into the chain
    new_node->next = front; 
	// TODO: return the new head of the chain if the function succeeded
    return new_node; 
}

