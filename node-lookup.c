#include "node.h"
#include <string.h>

Node *node_lookup(Node *front, const char *id) {
	// TODO: step through the chain pointed to by front
	// use function like strcmp to compare the id to the current node
	// if found return a pointer to the node, else return NULL

	Node *item_samelist = front; //pointer aliases

	while (item_samelist != NULL){
		if (strcmp(id, item_samelist->id)==0){
			return item_samelist;
		}
		else{
			item_samelist = item_samelist->next;
		}
	}


	return NULL; // does not find a match id
}
