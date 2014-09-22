#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definiera binärt sökträd
typedef struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
} *Node;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

Node insertNode(Node node, Node tree){
  if (tree == NULL) {
    tree = node;
    return tree;
  }

  int compare = strcmp(node->key, tree->key);
  printf("checking %s vs %s with result %d\n", node->key, tree->key, compare);

  if (compare < 0 && tree->left == NULL){
    tree->left = node;
    puts("writing left");
    return tree;
  }
  if (compare < 0 && tree->left != NULL){
      puts("going left");
      insertNode(node, tree->left);
      return tree;
    }
  
  if (compare > 0 && tree->right == NULL){
    puts("writing right");
    tree->right = node;
    return tree;
  }
  if (compare > 0 && tree->right != NULL){
    puts("going right");
    insertNode(node, tree->right);
    return tree;
  } 
  puts("Done");
  return tree;
}

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

Node findMatch(char *key, Node tree, int *found){
  //Node cursor = tree;
  //char target = tree->key;

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

void map(Node node){

  Node left = nextLeftNode(node);
  printDatabase(left);

  Node right = nextRightNode(node);
  printDatabase(right);
}


Node nextLeftNode(Node node){
  if (node->left == NULL){
    return NULL;
  }
  else {return node->left;}
}

Node nextRightNode(Node node){
  if (node->right == NULL){
    return NULL;
  }
  else {return node->right;}
}


void setValue(char *newValue, Node node){
  if (node != NULL){
    free(node->value);
    node->value = malloc(strlen(newValue) + 1);
    strcpy(node->value, newValue);
  }
}

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
