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

// Returns an int that corresponds to the desired action
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

// Find and print the name and value of a node
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

// Change the value of a node in the database
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
    setValue(buffer, match);
    puts("Value inserted successfully!");
      }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  
}

// Returns the database with an new entry inserted
Node newEntry(Node list){
  char newKey[128];
  char newValue[128];
  printf("Enter key: ");
  readline(newKey, 128, stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  Node match = findMatch(newKey, list, &found);
  
  if(found && match != NULL){
    printf("key \"%s\" already exists!\n", newKey);
  }
  
  if(!found){ 
    // Insert new node
    puts("Key is unique!\n");
    printf("Enter value: ");
    readline(newValue, 128, stdin);
    Node node = newNode(newKey, newValue);
    list = insertNode(node, list);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", newKey, newValue);
  }
  return (list);
} 



Node delete(Node list){
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  int success = 0;
  Node target = findMatch(buffer, list, &found);
  if (target == NULL) { 
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
    return list;
  }

  char* deletedKey = malloc(sizeof(findKey(target) + 1));
  char* deletedValue = malloc(sizeof(findValue(target) + 1));
  strcpy(deletedKey, findKey(target));
  strcpy(deletedValue, findValue(target));  
  list = deleteMatch(buffer, list, &success);
  if(success){
    printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", deletedKey, deletedValue);
  } 
  
  free(deletedKey);
  free(deletedValue);
  return (list);
  
}

// Print the database to terminal
void printDatabase(Node node){
  if (node != NULL){ 
    puts(findKey(node));
    puts(findValue(node));
    map(node);
  }
}

// Main function
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
  
  // Read the database
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
      list = newEntry(list);
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
