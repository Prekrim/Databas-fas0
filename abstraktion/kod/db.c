// Inkludera div biblotek
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiera nod
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

void printDatabase(Node list){
      // Print database
      Node cursor = list;
      while(cursor != NULL){
        puts(cursor->key);
        puts(cursor->value);
        cursor = cursor->next;
      }
}

Node readDatabase(char *filename, Node list, char buffer[]){
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  
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
void query(char buffer, Node list){
 
  printf("Enter key: ");
  readline(&buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL) {
    if(strcmp(&buffer, cursor->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
          found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", &buffer);
  }
  
}

void update(char buffer, Node list){
  // Update
  printf("Enter key: ");
  readline(&buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(&buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", &buffer);
  }else{
    printf("Enter new value: ");
    readline(&buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(&buffer) + 1);
    strcpy(cursor->value, &buffer);
    puts("Value inserted successfully!");
      }

}

Node newEntry(char buffer, Node list){
  // Insert
  printf("Enter key: ");
  readline(&buffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(&buffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  
  if(!found){ // Insert new node to the front of the list
    puts("Key is unique!\n");
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(&buffer) + 1);
    strcpy(newNode->key, &buffer);
    printf("Enter value: ");
    readline(&buffer, 128, stdin);
    newNode->value = malloc(strlen(&buffer) + 1);
    strcpy(newNode->value, &buffer);
    newNode->next = list;
    list = newNode;
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", list->key, list->value);
  }
  return (list);
} 

Node delete(char buffer, Node list){
  // Delete
  printf("Enter key: ");
  readline(&buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(&buffer, cursor->key) == 0){
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
    printf("Could not find an entry matching key \"%s\"!\n", &buffer);
  }
  return (list);
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
  char buffer[128];
  Node list = NULL;
  
  
  list = readDatabase(filename, list, buffer);


  // Main loop
 
  
  // Choose the desired operatio
  int choice = chooseIndex(); 
  
  while(choice != 0){
    
    switch(choice){
      
    case 1:
      query(*buffer, list);
      break;

      
    case 2:
      
      update(*buffer, list);
      break;
    
    case 3:
      
      list = newEntry(*buffer, list);
      break;

    case 4:
     
      list = delete(*buffer, list);
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
