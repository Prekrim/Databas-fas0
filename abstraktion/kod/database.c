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

// Returns the tree with a node removed that has a key string matching buffer, if there is none it returns the unmodified tree. 
Node deleteMatch(char *buffer, Node tree, int *success){

  int found = 0;
  int path = 0;
  Node cursor = findMatch(buffer, tree, &found);
  if (cursor == NULL){return tree;}
  Node prev = tree;
  prev = prevNode(prev, cursor, &path);
  
  while(found && cursor != NULL){
    *success = 1;
    if(prev == NULL){ // Delete first node
      if(tree->left == NULL && tree->right == NULL){
	return NULL;
      }else if(tree->left == NULL){
	tree = tree->right;
	clearNode(cursor);
	return tree;
      }else if(tree->right == NULL){
	tree = tree->left;
	clearNode(cursor);
	return tree;
      }else{
        tree = insertNode(tree->right, tree->left);
	clearNode(cursor);
	return tree;
      }
    }
    else if(cursor->left == NULL && cursor->right == NULL){ // Delete leaf
      printf("Target is a leaf");
      printf("Previous is %s ", prev->key);
      if(path == 1){ // Leaf is left of parent node
	prev->left = NULL;
	
      }else{ // Leaf is right of parent node
	prev->right = NULL;
      }
      clearNode(cursor);
      return tree;
    }
    else{ // Delete current node
      printf("Target is node\n");
      if(path == 1){ // Current node is left of previous node
	printf("Current node is left of previous node");
	if(cursor->left == NULL){
	  printf("Current node has no left node");
	  prev->left = cursor->right;
	  
	}else if(cursor->right == NULL){
	  prev->left = cursor->left;
	}else{
	  insertNode(cursor->right, cursor->left);
	  prev->left = cursor->left;
	}
      }else{ // Current node is right of previous node
	if(cursor->left == NULL){
	  prev->right = cursor->right;
	}else if(cursor->right == NULL){
	  prev->right = cursor->left;
	}else{
	  insertNode(cursor->right, cursor->left);
	  prev->right = cursor->left;
	}
      }
      clearNode(cursor);
      return tree;
    }
  }
  return tree;
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

// Sets the key in node to newkey.
void setKey(char *newKey, Node node){
  if(node != NULL)
    {
      node->key=newKey;
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

Node prevNode(Node prev, Node searchNode, int *path){
  if(searchNode->key != prev->key && prev != NULL){
    if(prev->left == searchNode){ // searchNode is left child of prev
      *path = 1;
      return prev;
    }else if(prev->right == searchNode){ // searchNode is right child of prev
      *path = -1;
      return prev;
    } else{ // searchNode is within either left or right sub tree, recursive search
      int compare = strcmp(prev->key, searchNode->key);
      if(compare > 0){
	*path = 1;
	printf("Prev is now %s\n", prev->key);
	prev = prevNode(prev->left, searchNode, path);
	printf("Prev is now %s\n", prev->key);
      }else{
	*path = -1;
	printf("Prev is now %s\n", prev->key);
	prev = prevNode(prev->right, searchNode, path);
      }

      return prev;
    }
  }
  return NULL;
}


void clearNode(Node node){
  free(node->key);
  free(node->value);
  free(node);
}
