// Inkludera div biblotek
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Funktionsprototyper
int chooseIndex();
void query(Node list);
void update(Node list);
Node newEntry(Node list);
void printDatabase(Node list);
Node delete(Node list);
int main(int argc, char *argv[]);

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

void update(Node list){
  char buffer[128];
  int found = 0;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  Node match = findMatch(buffer, list, &found);
  if (match != NULL){
    puts("Matching entry found:");
    char *key = findKey(match);
    char *value = findValue(match);
    printf("key: %s\nvalue: %s\n\n", key, value);
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    setKey(buffer, match);
    puts("Value inserted successfully!");
      }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  
}
/*
Node newEntry(Node list){
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
/*
Node delete(Node list){
  // Delete
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
	list = cursor->next;
      }else{
	prev->next = cursor->next;
      }
      found = 1;
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  return (list);
}
*/

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
      update(list);
      break;
    
    case 3:
      //list = newEntry(list);
      break;

    case 4:     
      //list = delete(list);
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
