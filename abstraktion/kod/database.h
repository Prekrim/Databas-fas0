#ifndef DATABASE_H 
#define DATABASE_H

#include <stdio.h>

// Declares the struct node
typedef struct node *Node;

// Returns a database created from the file filename
Node readDatabase(char *filename);

// If a key in list matches the key in buffer, returns the node thatcontains the key, else returns NULL  
Node findMatch(char *buffer, Node list, int *found);

// Returns the key contained in node
char *findKey(Node node);

// Returns the value contained in node
char *findValue(Node node);

// Inserts the content in source to the destination dest
void readline(char *dest, int n, FILE *source);

// Returns the left node connected node
Node nextLeftNode(Node node);

// Returns the right node connected to node
Node nextRightNode(Node node);

// Returns node with buffer as value
//Node updateNode(char buffer, Node node);

// Returns node with buffer as value
void setValue(char *newValue, Node node);

// Returns a node with key and value corresponding to the input key and value
Node newNode(char *key, char *value);

// Returns tree with node inserted
Node insertNode(Node node, Node tree);

// Calls printDatabase with the left and right nodes of node
void map(Node node);

// Prints the key and value of the node database, and calls map with database
void printDatabase(Node database);

#endif
