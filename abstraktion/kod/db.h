#ifndef DB_H 
#define DB_H

/**
 * @file db.h
 * @author Jonas Karlsson & Oliver Stein
 * @brief A simple database program with key-value pairs.

 * This is a simple database program which creates a database from a file, and then allows modification of the database inside the program (no changes are made to the actual file). There is functionality for adding, querying, removing and updating entries, as well as printing out the database as the key-value pairs.
 */


Node createDatabase(char *filename);


int chooseIndex();


void query(Node list);


void update(Node list);


Node newEntry(Node list);


void printDatabase(Node list);


Node delete(Node list);


//int main(int argc, char *argv[]);

#endif
