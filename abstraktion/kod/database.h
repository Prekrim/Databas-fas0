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
Node updateNode(char buffer, Node node);
void setKey(char *newKey, Node node);

#endif
