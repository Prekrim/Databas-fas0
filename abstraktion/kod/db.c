// Inkludera div biblotek
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Funktionsprototyper
//void readline(char *dest, int n, FILE *source);
//Node readDatabase(char *filename);
int chooseIndex();
void query(Node list);
void update(Node list);
Node newEntry(Node list);
void printDatabase(Node list);
Node delete(Node list);
int main(int argc, char *argv[]);

/*Node readDatabase(char *filename){
  printf("Loading database \"%s\"...\n\n", filename);
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
*/

/*

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}
  */

int chooseIndex(){
  int choice;
  
  puts("Please choose an operation");
  puts("1. Query a key");
  puts("2. Update an entry");
  puts("3. New entry");
  puts("4. Remove entry");
  puts("5. Print database");
  puts("0. Exit database");
  printf("? ");
  scanf("%d", &choice);
  while(getchar() != '\n'); // Clear stdin
  
  return (choice);  
}
void query(Node list){
  char buffer[128]; 
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node match = findMatch(buffer, list, &found);
  char *key = findKey(match);
  char *val = findValue(match);

  if(found){
    puts("Found entry:");
    printf("key: %s\nvalue: %s\n", key, val);   
  }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
}

  /*
  while(!found && cursor != NULL) {
    if(strcmp(buffer, cursor->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
          found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  
}
*/

/*
void update(Node list){
  // Update
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int *found = 0;
  Node cursor = list;


  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }else{
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!");
      }

}

*/

/*
Node newEntry(Node list){
  // Insert
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  
  if(!found){ // Insert new node to the front of the list
    puts("Key is unique!\n");
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    printf("Enter value: ");
    readline(buffer, 128, stdin);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", list->key, list->value);
  }
  return (list);
} 
*/
Node delete(Node list){
  // Delete
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  int success = 0;
  Node target = findMatch(buffer, list, &found);
  list = deleteMatch(buffer, list, &success);
  /*
  Node cursor = findMatch(buffer, list, &found);
  Node prev = list;
  prev = prevNode(prev, cursor);
   
  while(found && cursor != NULL){
    if(prev == NULL){ // Delete first node
      list = nextNode(cursor);
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", findKey(cursor), findValue(cursor));
      return list;
    }else if(nextNode(cursor) == NULL){ // Delete last node
      setNextNode(prev, NULL);
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", findKey(cursor), findValue(cursor));
      return list;
    }else
      setNextNode(prev, nextNode(cursor));
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", findKey(cursor), findValue(cursor));
      return list;
    
  }
  */
  if(success){
    printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", findKey(target), findValue(target));
  } 
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  
  return (list);
  
}

void printDatabase(Node list){
  Node cursor = list;
  while(cursor != NULL){
    puts(findKey(cursor));
    puts(findValue(cursor));
    cursor = nextNode(cursor);
  }
}


int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  // Read the input file
  char *filename = argv[1];
  
  // Läs in databasen
  printf("Loading database \"%s\"...\n\n", filename);
  Node list = readDatabase(filename);

  // Main loop  
  // Choose the desired operation
  int choice = chooseIndex();  
  while(choice != 0){
    
    switch(choice){
      
    case 1:
      query(list);
      break;
      
    case 2:
      //update(list);
      break;
    
    case 3:
      //list = newEntry(list);
      break;

    case 4:     
      list = delete(list);
      break;
   
    case 5:
      printDatabase(list);
      break;

    case 0:
      // Exit
      puts("Good bye!");
      break;

    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
    choice = chooseIndex();

  }
  return 0;
}
