Databas-fas0
============

Databasen till fas0, sprint 1.

För att bygga programmet:

Alternativ 1
	To choose input file:
	make db
	./db [INPUT FILE]
	
	(or) 
	To use default input file:
	make db	
	make run

Alternativ 2
	gcc -Wall -ggdb -std=c99 -o db db.c database.c
	./db [INPUT FILE]

Mål som redovisats med detta program:
T53
A1
M37
K30
M38
U55
J26
M36
R50
A3

Eventuella utökningar:
-En funktion som balanserar sökträdet.
-En funktion som avgör vad som är godtagbar indata.
-En funktion som slumpar ut ett givet antal noder ur databasen.

Övrigt:
-Databashanteraren ser inte skillnad på strängar med versaler, gemener, numeriska tal, specialtecken osv. 
 Detta är på grund av att vi inte vet vad som databasen förväntas innehålla.
-Databashanteraren har ett dubbel
