#ifndef _NODE_H
#define _NODE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct node {
	char *id;
	char *purchased_item;
	double cost;
	struct node *next;
} Node;

Node *node_lookup(Node *front, const char *id);
Node *make_node(Node *front, char *id, char *purchased_item, double cost);
bool load_table(Node **htable, size_t table_size, const char *filename);
unsigned long hash(char *id);
void delete_table(Node **htable, size_t table_size);
void print_info(Node **htable, size_t table_size, unsigned long threshold);

#endif
