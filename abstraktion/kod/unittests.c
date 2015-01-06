#include <string.h>
#include "CUnit/Basic.h"
#include <stdlib.h>
#include "database.h"
#include "db.h"

// Function Specifiacations from modules
Node newNode(char *key, char *value);
char *findKey(Node node);
char *findValue(Node node);

int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}

void testReadDatabase(void)
{
  Node db = readDatabase("SWE.db");
  CU_ASSERT(db != NULL);
  clearDatabase(db);
}

void testInsertNode(void)
{
  Node db = readDatabase("SWE.db");
  char* key = "Filip";
  char* value = "21";
  Node createdNode = newNode(key, value);
  insertNode(createdNode, db);
  int found = 0;
  Node match = findMatch("Filip", db, &found);
  CU_ASSERT(found == 1);

  found = 0;
  Node emptyNode = newNode(NULL, NULL);
  insertNode(emptyNode, db);  
  Node noMatch = findMatch(NULL, db, &found);
  CU_ASSERT(found == 0);
  clearDatabase(db);
}

void testFindMatch(void)
{
  Node db = readDatabase("SWE.db");
  int found = 0;
  Node match = findMatch("Diana", db, &found);
  CU_ASSERT(found == 1);

  found = 0;
  match = findMatch("", db, &found);
  CU_ASSERT(found == 0);

  found = 0;
  match = findMatch("¤%!¤!A#%&", db, &found);
  CU_ASSERT(found == 0);

  found = 0;
  match = findMatch(NULL, db, &found);
  CU_ASSERT(found == 0);
}

void testDeleteMatch(void)
{
  Node db = readDatabase("SWE.db");
  int found = 0;
  char key[5] = "Anna\0";
  Node match = findMatch(key, db, &found);
  CU_ASSERT(match != NULL);
  CU_ASSERT(found = 1);

  found = 0;
  int success = 0;
  db = deleteMatch(key, db, &success);
  Node empty = findMatch(key, db, &found);
  CU_ASSERT(empty == NULL);

  clearDatabase(db);  
}

void testNewNode(void)
{
  Node createdNode = newNode("Filip", "21"); 
  CU_ASSERT(createdNode != NULL);
  char* key = findKey(createdNode);
  char* value = findValue(createdNode);
  int k = strcmp("Filip", key);
  int v = strcmp("21", value);
  CU_ASSERT(k == 0);
  CU_ASSERT(v == 0);

  Node keyNode = newNode(NULL, "11");
  Node valueNode = newNode("Filip", NULL);
  Node nullNode = newNode(NULL, NULL);
  Node emptyNode = newNode("", "");
  CU_ASSERT(keyNode == NULL);
  CU_ASSERT(valueNode == NULL);
  CU_ASSERT(nullNode == NULL);
  key = findKey(emptyNode);
  value = findValue(emptyNode);
  k = strcmp("", key);  
  v = strcmp("", value);
  CU_ASSERT(k == 0);
  CU_ASSERT(v == 0);

  clearNode(createdNode);    
  clearNode(keyNode);    
  clearNode(valueNode);
  clearNode(nullNode);
  clearNode(emptyNode);            
}

int main(void)
{
  CU_pSuite pSuite1 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("\tTrace Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suite */
  if((NULL == CU_add_test(pSuite1, "Test of creating a database", testReadDatabase)) || 
     (NULL == CU_add_test(pSuite1, "Test of inserting a node in a database", testInsertNode)) ||
     (NULL == CU_add_test(pSuite1, "Test of finding a node by matching", testFindMatch)) ||
     (NULL == CU_add_test(pSuite1, "Test of finding and deleting a node by matching", testDeleteMatch)) ||
     (NULL == CU_add_test(pSuite1, "Test of creating a new node", testNewNode))
     ){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
