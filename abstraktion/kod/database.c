#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definiera binärt sökträd
typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}
/*
void updateNode(char buffer, Node node){
    free(node->value);
    node->value = malloc(strlen(&buffer) + 1);
    strcpy(node->value, &buffer);
    return node;
}
*/

Node readDatabase(char *filename){

  FILE *database = fopen(filename, "r");
  Node list = NULL;
  char buffer[128];

  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node));
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, 128, database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
  }
  return list;

}

Node findMatch(char *buffer, Node list, int *found){
  Node cursor = list;
  
  while(cursor != NULL) {
    if(strcmp(buffer, cursor->key) == 0) {
      *found = 1;
      return cursor;
    }
    else {cursor = nextNode(cursor);}
  }
  return cursor;
}

char *findKey(Node node){
  if (node == NULL){
    return NULL;
  }
  else{return node->key;}
}

char *findValue(Node node){
  if (node == NULL){
    return NULL;
  }  
  else{return node->value;}
}

Node nextNode(Node node){
  if (node->next == NULL){
    return NULL;
  }
  else {return node->next;}
}


void setKey(char *newKey, Node node){
  if (node != NULL){
    free(node->value);
    node->value = malloc(strlen(newKey) + 1);
    strcpy(node->value, newKey);
  }
}
