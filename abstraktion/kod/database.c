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

Node deleteMatch(char *buffer, Node list, int *success){

  int found = 0;
  Node cursor = findMatch(buffer, list, &found);
  Node prev = list;
  prev = prevNode(prev, cursor);
  
  while(found && cursor != NULL){
    *success = 1;
    if(prev == NULL){ // Delete first node
      list = cursor->next;
      return list;
    }
    else if(nextNode(cursor) == NULL){ // Delete last node
      setNextNode(prev, NULL);
      return list;
    }
    else{ // Delete current node
      setNextNode(prev, nextNode(cursor));
      return list;
    }
  }
  return list;
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
  if(node != NULL)
    {
      node->key=newKey;
    }
}

void setValue(char *newValue, Node node){
  if(node != NULL)
    {
      node->value=newValue;
    }
}


void setNextNode(Node node, Node newNode){
  if(node != NULL)
    {
      node->next = newNode;
    }
}

Node prevNode(Node node, Node searchNode){
  if(searchNode == NULL){
    return NULL;
  }else
    while(node != NULL){
      if(node->next == searchNode){
	return node;
      }
      node = node->next;
    }
  return node;
}
