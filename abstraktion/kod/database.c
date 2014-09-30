#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define binary tree
typedef struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
} *Node;

// Read a line from source and put it into dest
void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

// Returns a tree with a node inserted into the tree
Node insertNode(Node node, Node tree){
  if (node == NULL) {
    return tree;
  }

  if (tree == NULL) {
    tree = node;
    return tree;
  }

  int compare = strcmp(node->key, tree->key);
  //printf("checking %s vs %s with result %d\n", node->key, tree->key, compare);

  if (compare < 0 && tree->left == NULL){
    tree->left = node;
    //puts("writing left");
    return tree;
  }
  if (compare < 0 && tree->left != NULL){
    //puts("going left");
      insertNode(node, tree->left);
      return tree;
    }
  
  if (compare > 0 && tree->right == NULL){
    //puts("writing right");
    tree->right = node;
    return tree;
  }
  if (compare > 0 && tree->right != NULL){
    //puts("going right");
    insertNode(node, tree->right);
    return tree;
  } 
  //puts("Done");
  return tree;
}

// Returns a new binary tree made from the input pointer filename
Node readDatabase(char *filename){

  FILE *database = fopen(filename, "r");
  Node tree = NULL;
  char key[128];
  char value[128];
    
    while(!(feof(database))){
      
      readline(key, 128, database);
      readline(value, 128, database);
      Node newTree = newNode(key, value);
      tree = insertNode(newTree, tree);
    }
  return tree;
}

// Find a matching node and return it, else return NULL
Node findMatch(char *key, Node tree, int *found){
  if (tree == NULL) {
    return NULL;
  }

  if(strcmp(key, tree->key) == 0) {
    *found = 1;
    return tree;
  }

  int compare = strcmp(key, tree->key);

  if (compare < 0){
    Node left = findMatch(key, nextLeftNode(tree), found);
    if (left != NULL) {return left;}
  }
  if (compare > 0){
    Node right = findMatch(key, nextRightNode(tree), found); 
    if (right != NULL) {return right;}
  }
  return NULL;
    
}

// Returns the input nodes key
char *findKey(Node node){
  if (node == NULL){
    return NULL;
  }
  else{return node->key;}
}

// Returns the input nodes value
char *findValue(Node node){
  if (node == NULL){
    return NULL;
  }  
  else{return node->value;}
}

// Recursively calls print database to print the tree
void map(Node node){

  Node left = nextLeftNode(node);
  printDatabase(left);

  Node right = nextRightNode(node);
  printDatabase(right);
}

// Returns the next left node, if there are none returns NULL
Node nextLeftNode(Node node){
  if (node->left == NULL){
    return NULL;
  }
  else {return node->left;}
}

// Returns the next right node, if there are none returns NULL
Node nextRightNode(Node node){
  if (node->right == NULL){
    return NULL;
  }
  else {return node->right;}
}

// Sets a new value for the input node
void setValue(char *newValue, Node node){
  if (node != NULL){
    free(node->value);
    node->value = malloc(strlen(newValue) + 1);
    strcpy(node->value, newValue);
  }
}

// Returns a new node
Node newNode(char *key, char *value){
  Node new = malloc(sizeof(struct node));
  new->key = malloc(strlen(key) + 1);
  strcpy(new->key, key);
  new->value = malloc(strlen(value) + 1);
  strcpy(new->value, value);
  new->left = NULL;
  new->right = NULL;
  return new;
}
