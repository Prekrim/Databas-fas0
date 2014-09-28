#ifndef DATABASE_H 
#define DATABASE_H

#include <stdio.h>

typedef struct node *Node;

Node readDatabase(char *filename);
Node findMatch(char *buffer, Node list, int *found);
char *findKey(Node node);
char *findValue(Node node);
void readline(char *dest, int n, FILE *source);

Node nextNode(Node node);

void setKey(char *newKey, Node node);
void setNextNode(Node node, Node newNode);

Node deleteMatch(char *buffer, Node list, int *success);
Node prevNode(Node prev, Node searchNode, int *path);

Node nextLeftNode(Node node);
Node nextRightNode(Node node);
Node updateNode(char buffer, Node node);
void setValue(char *newValue, Node node);
Node newNode(char *key, char *value);
Node insertNode(Node node, Node tree);
void map(Node node);
void printDatabase(Node database);

// Frigör minnet för en nod, inklusive dess innehåll
void clearNode(Node node);

#endif
